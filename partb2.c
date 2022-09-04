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
while (pch != NULL)
{

 mycmds[ctr1]=strdup(pch);
// printf("%s\n",mycmds[ctr1]);
 pch = strtok (NULL, " \n");
 ctr1++ ;
}
//this is used to seperate the string on a the basis of delimeter, in this case space and \n
mycmds[ctr1]=NULL;
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
}
}
 return 0;
}
