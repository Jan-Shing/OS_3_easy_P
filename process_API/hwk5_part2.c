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
		printf("hello!!\n");
		ret = wait(&status);
		if(ret < 0)
			perror("wait fail...");
		else
			printf("After wait in child: %d\n", status);
	}else{
		wait(NULL);
		printf("good bye\n");
	}
	
return 0;
}
