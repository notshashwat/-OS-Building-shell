#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <string.h>
#include <sys/wait.h>
int MAX_LIMIT=1000;

void newexec(char * cmd, char** argv){
	int p[2];
	pipe(p);
	if(fork()==0){//child process 
	dup2(p[1],1);//now the stdout is connected to pipe write
	close(p[0]);//pipe read is closed off
	}
	else{//parent process
	dup2(p[0],0);//now the stdin is connect with pipe read
	close(p[1]);
	execvp(cmd,argv);//excute the command in the parent process while the child works on further pipes
	}
}

int main(int argc, char *argv[])
{
while (1){
char cmd[MAX_LIMIT];
printf("Shashwat@12041380>");
fgets(cmd, MAX_LIMIT, stdin);
if (strcmp(cmd,"exit\n")==0){break;}
//logic to exit the bash
char *mycmds[MAX_LIMIT];



char * pch;
pch = strtok (cmd," \n");
int ctr1=0;
while (pch != NULL)
{

 mycmds[ctr1]=strdup(pch);
 pch = strtok (NULL, " \n");
 ctr1++ ;
}
//this is used to seperate the string onn a the basis of delimeter, in this case space and \n
mycmds[ctr1]=NULL;
//mycmd now contains array of form {"ls","|","grep",".c"}
if (fork()==0){//forking out to start running the commands
for (int i=ctr1-1;i>=1;i--){
//starting from the right most command , we execute each chunk seperated by pipe symbol | 
//note that it is crucial in the input to give space between cmd and pipe(which is different from normal bash)
	if(!strcmp(mycmds[i],"|")){
		mycmds[i]=NULL;
		newexec(mycmds[i+1], &mycmds[i+1]); //this function creates a child to run commands 
		//left of the current commands and deal with pipes
		
	}
	
}
execvp(mycmds[0],&mycmds[0]); // we leave the last command (left most one) to be outputted
//directly to the stdout , and hence the function newexec is not called for this one
}
else{
wait(NULL);// this fork and wait is important to do because otherwise the overall while loop will 
//end after the first bash command only 
}
}
 return 0;

}
