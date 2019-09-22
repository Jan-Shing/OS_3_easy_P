#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sched.h>

#define TEST_FILE "try.txt"

int main(void){
    int fd, loops;
    struct timeval start, end;
    size_t i;
    int first_pipe[2], second_pipe[2];

    loops = 10000000;
    fd = open(TEST_FILE, O_CREAT | O_WRONLY | O_TRUNC);
    if (fd < 0)
        printf(" can't open file: %s", TEST_FILE);

    /* measeure system call*/
    gettimeofday(&start, NULL);
    for(i = 0; i < loops; i++)
        read(fd, NULL, 0);
    gettimeofday(&end, NULL);
    printf("system call: %f microseconds\n\n", 
          (float) (end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec) / loops);
    close(fd);

    /* measure context switch*/
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);

    if(pipe(first_pipe) == -1){
        perror("pipe first");
        exit(EXIT_FAILURE);
    }
    if(pipe(second_pipe) == -1){
        perror("pipe second");
        exit(EXIT_FAILURE);
    }

    int rc = fork();
    if(rc < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }else if (rc == 0){
        if(sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) < 0)
            exit(EXIT_FAILURE);
        for(i = 0; i < loops; i++){
            read(first_pipe[0], NULL, 0);
            write(second_pipe[1], NULL, 0);
        }
    }else{
        if(sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) < 0)
            exit(EXIT_FAILURE);
        gettimeofday(&start, NULL);
        for(i = 0; i < loops; i++){
            write(first_pipe[1], NULL, 0);
            read(second_pipe[0], NULL, 0);
        } 
        gettimeofday(&end, NULL);
        printf("context switch: %f microseconds\n",
              (float) (end.tv_sec * 1000000 + end.tv_usec - start.tv_sec * 1000000 - start.tv_usec) / loops);
    }
    return 0;
}

