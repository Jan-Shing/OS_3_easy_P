#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]){
	int ret;
	int pfd[2];
	
	if(pipe(pfd) == -1){
		printf(" generating pipe fail....\n");
		exit(1);
	}

	ret = fork();
	if(ret < 0){
		printf("fork failed1, exit....\n");
		exit(1);
	}else if(ret == 0){
		close(pfd[0]);  //close unused read end
		if(dup2(pfd[1], STDOUT_FILENO) == -1){
			printf("replace standard output fail...\n");
			_exit(1);
		}

		execlp("ls", "ls", NULL);
	}
	
	ret = fork();
	if(ret < 0){
		printf("fork failed2, exit....\n");
		exit(1);
	}else if(ret == 0){
		close(pfd[1]);  //close unused read end
		if(dup2(pfd[0], STDIN_FILENO) == -1){
			printf("replace standard input fail...\n");
			_exit(1);
		}

		execlp("wc", "wc", "-l", NULL);
	}else{
		close(pfd[0]);
		close(pfd[1]);
		wait(NULL);
		printf("time to leave!!\n");
		wait(NULL);
		printf("time to leave2!!\n");
	}


	
	
return 0;
}
