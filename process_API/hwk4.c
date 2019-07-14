#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main (int argc, char *argv[]){
	int ret;
	unsigned char cmd;
	char *arg = NULL;
	extern char** environ;
	
	if (argc < 2){
		printf("Usage: <number> parameter\n");
		printf("0.execl  1.execlp 2.execle 3.execv 4.execvp 5.execve \n");
		printf("for execl series command: only need command number to do ls -al\n");
		printf("for execv series command: need command arguments to do what command you want\n");
		exit(1);
	}

	
	cmd = atoi(argv[1]);

	ret = fork();
	if(ret < 0){
		printf("fork failed, exit....\n");
		exit(1);
	}else if(ret == 0){
	switch(cmd){
	case 0:
		ret = execl("/bin/ls", "ls", "-al", NULL );
		if(ret == -1)
			perror("execl");
		break;
	case 1:
		ret = execlp("ls", "ls", "-al", NULL);
		if(ret == -1)
			perror("execlp");
		break;
	case 2:
		ret = execle("/bin/ls", "ls", "-al", NULL, environ);
		if(ret == -1)
			perror("execle");
		break;
	case 3:
		ret = execv(argv[2], &argv[2]);
		if(ret == -1)
			perror("execle");
		break;
	case 4:
		ret = execvp(argv[2], &argv[2]);
		if(ret == -1)
			perror("execle");
		break;
	case 5:
		ret = execve(argv[2], &argv[2],environ);
		if(ret == -1)
			perror("execle");
		break;
	default:
		printf("please input command number in 1~5\n");
		break;
	}

	}else{
		wait(NULL);
	}
	
return 0;
}
