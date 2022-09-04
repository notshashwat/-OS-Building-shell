#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <string.h>
#include <sys/wait.h>
int MAX_LIMIT=1000;



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
//this is used to seperate the string on a the basis of delimeter, in this case space and \n

while (pch != NULL)
{

 mycmds[ctr1]=strdup(pch);
 //printf("%s\n",mycmds[ctr1]);
 pch = strtok (NULL, " \n");
 ctr1++ ;
}
int redflag=0;
int stdout_fd = 1;
//logic for redirection:
if(!strcmp(mycmds[ctr1-2],">")){
redflag=1;//to remember to reopen the stdout file descriptor after job is done
// Making a copy of STDOUT
stdout_fd = dup(1);

//closing the stdout
close(STDOUT_FILENO);

//opening the fd to new file 
open(mycmds[ctr1-1], O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
mycmds[ctr1-2]=NULL;//limit the commands section to before the >
ctr1=ctr1-2;
}
else{//no redirection is to be done

mycmds[ctr1]=NULL;
}

//mycmds now contains array of form {"ls","&&","ps"}

if (fork()==0){//forking out to start running the commands
int l=0; //just a pointer to the left hand side of the current && chunk
for (int i=0;i<ctr1;i++){
	if(!strcmp(mycmds[i],"&&")||mycmds[i]==NULL){
		mycmds[i]=NULL; 
		if(fork()==0){	
			
			if (execvp(mycmds[l], &mycmds[l])<0){
				printf("command: %s has failed\n",mycmds[l]);
				break;
			}
				}
			
		else{
		
		wait(NULL);
		
			}
			
		l=i+1;
	
}
}
execvp(mycmds[l],&mycmds[l]);
}
else{
wait(NULL);// this fork and wait is important to do because otherwise the overall while loop will 
//end after the first bash command only 
if (redflag==1){ 
// Restoring STDOUT
dup2(stdout_fd, 1);}
}
}
 return 0;
}
