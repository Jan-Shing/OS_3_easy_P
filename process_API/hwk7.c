#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main (int argc, char *argv[]){
	int ret;
	int status;
	int magic = 5566;
	int fd;

	ret = fork();
	if(ret < 0){
		printf("fork failed, exit....\n");
		exit(1);
	}else if(ret == 0){
		close(STDOUT_FILENO);
		fd = open("test", O_CREAT | O_RDWR | O_TRUNC);
		printf("hello!!, my pid is %d and i will print it in %d\n",getpid(),fd);
		close(fd);
		_exit(magic);
	}else{
		ret = waitpid(0, &status, 0);
		if (ret > 0){
			printf("the status from wait() is %d\n",status);
			printf("ret return from wait is %d and my pid is %d\n", ret, getpid());
			if(WIFEXITED(status))
				printf("Normal ternination with exit status = %d\n",WIFEXITED(status));
		}
	}
	
return 0;
}
