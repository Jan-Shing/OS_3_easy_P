#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main (int argc, char *argv[]){
	char x[8] = {0};  // see if this variable shared by parent and child process
	int ret;

	ret = fork();
	if(ret < 0){
		printf("fork failed, exit....\n");
		exit(1);
	}else if(ret == 0){
		printf("x is %s in child process\n",x);
		sprintf(x, "%s","child");
		printf("x then to be  %s in child process\n",x);
	}else{
		wait(NULL);
		printf("x is %s after child process\n",x);
		sprintf(x, "%s","parent");
		printf("x then to be  %s in parent process\n",x);
	}
	
return 0;
}
