#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int MAX_LIMIT=1000;
int
main(int argc, char *argv[])
{
while (1){
char cmd[MAX_LIMIT];
printf("Shashwat@12041380>");
fgets(cmd, MAX_LIMIT, stdin);
 //exit logiv
 if (strcmp(cmd,"exit\n")==0){break;}
 int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
	
        char *myargs[MAX_LIMIT];

	char * pch;
  	pch = strtok (cmd," \n");
  	int ctr=0;
	while (pch != NULL)
  	{
  	 myargs[ctr]=strdup(pch);
	 pch = strtok (NULL, " \n");
	 ctr++ ;
	}


        myargs[ctr] = NULL;           // marks end of array
	if (strcmp(myargs[0],"cd")==0){chdir(myargs[1]);}
	else{
	execvp(myargs[0], myargs);}  // runs the command
    } else {
        int wc = wait(NULL);
}



}


 return 0;
}
