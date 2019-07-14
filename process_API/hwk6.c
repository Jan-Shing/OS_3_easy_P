#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]){
	int ret;
	int status;
	int magic = 5566;

	ret = fork();
	if(ret < 0){
		printf("fork failed, exit....\n");
		exit(1);
	}else if(ret == 0){
		printf("hello!!, my pid is %d\n",getpid());
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
