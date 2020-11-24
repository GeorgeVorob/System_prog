#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>

void* input(void *pipe) {
    printf("Input thread started\n");
    int *myPipe;
    myPipe = pipe;
    if(myPipe == NULL) {printf("pipe transmission fail"); exit(1); }
    //close(myPipe[0]);
    printf("Input thread pipe end:%d\n", myPipe[1]);

    char str[] = "aaaaaaaaaaAaaaaaaaa";
    write(myPipe[1],str,strlen(str));
    sleep(3);
    strcpy(str,"_bbbBbb");
    write(myPipe[1],str,strlen(str));
}

void* output(void *pipe) {
    printf("Output thread started\n");
    int *myPipe;
    myPipe = pipe;
    if(myPipe == NULL) {printf("pipe transmission fail"); exit(1); }
    //close(myPipe[1]);
    printf("Output thread pipe end:%d\n", myPipe[0]);
    fflush(stdout);

    char ch;
    ssize_t ret;
    while (ret = read(myPipe[0], &ch, 1) >= 0)
    {
    printf("%c",toupper(ch));
    fflush(stdout);
    }  

    if(ret == -1)
    {
        perror("pipe output error: ");
        exit(1);
    }

    printf("here3\n");
    fflush(stdout);
}

int main(int argc, char ** argv) {
    printf("program started\n");

    int fd[2];
    if (pipe(fd) == -1) { perror("pipe creating error: "); exit(1); }
    printf("pipe created:\n fd[0]: %d\n fd[1]: %d\n", fd[0], fd[1]);

    pthread_t inputThread;
    pthread_t outputThread;

    pthread_create(&inputThread, NULL, input, (void *)fd);
    pthread_create(&outputThread, NULL, output, (void *)fd);

    pthread_join(inputThread, NULL);
    pthread_join(outputThread, NULL);
    return 0;
}