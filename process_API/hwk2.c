 #include <stdio.h>                                                                                                                                                                                       
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
 #include <limits.h>
 #include <sys/wait.h>
 #include <sys/types.h>
 #include <fcntl.h>
  
#define FILE_NAME "normal_file"

int main (int argc, char *argv[]){
    int fd;  // see how file descripter shared by parent and child process
    int ret;
    char *data_c = "child_data\n";
    char *data_p = "parent_data\n";
    int count = 2000000;
    int i;

    fd = open(FILE_NAME, O_CREAT | O_TRUNC | O_RDWR);
    if (fd == -1){
        printf("Can't open file: %s\n", FILE_NAME);
        exit(1);
    }

    ret = fork();
    if(ret < 0){
        printf("fork failed, exit....\n");
        close(fd);
        exit(1);
    }else if(ret == 0){
        for (i=0;i<count;i++)
            write(fd, data_c, strlen(data_c));
    }else{
        for (i=0;i<count;i++)
            write(fd, data_p, strlen(data_p));
        wait(NULL);
        close(fd);
    }

return 0;
}
