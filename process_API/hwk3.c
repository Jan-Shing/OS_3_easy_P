#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]){
	char x[8] = {0};  // see if this variable shared by parent and child process
	int ret;
	int pfd[2];
	char dummy;
	
	if(pipe(pfd) == -1){
		printf(" generating pipe fail....\n");
		exit(1);
	}

	ret = fork();
	if(ret < 0){
		printf("fork failed, exit....\n");
		exit(1);
	}else if(ret == 0){
		close(pfd[0]);  //close unused read end
		printf("hello!!\n");
		write(pfd[1], 0, 1);
		close(pfd[0]);
		_exit(0);
	}else{
		
		close(pfd[1]);  //close unused write end
		read(pfd[0], &dummy, 1);
		printf("goodbye!!\n");
		close(pfd[0]);
	}
	
return 0;
}
