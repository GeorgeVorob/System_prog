#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>

//static sem_t* mySemaphoreA;
//static sem_t* mySemaphoreB;

struct threadArgs
{
    int threadNum;
    sem_t* sem1;
    sem_t* sem2;
}args1, args2;


void* incr_counter(void *input) {
    printf("Thread %d start\n",((struct threadArgs*)input)->threadNum);
    int counter = 0;
    do {
        //sleep(1);
        counter++;
        sem_wait(((struct threadArgs*)input)->sem1);
        int logfile = open("./lab_4_logs.txt",O_CREAT | O_WRONLY | O_APPEND);

        if(logfile == -1){perror("File open error"); _exit(1);}
        dprintf(logfile, "Thread %d counter %d\n", ((struct threadArgs*)input)->threadNum, counter);
        printf("Thread %d counter %d\n", ((struct threadArgs*)input)->threadNum, counter);
        //sleep(1);

        close(logfile);
        sem_post(((struct threadArgs*)input)->sem2);
    } while ( counter<10 );
}

int main(int argc, char ** argv) {
    printf("program started\n");
    sem_t* mySemaphoreA;
    sem_t* mySemaphoreB;
    pthread_t thread_1;
    pthread_t thread_2;

    int logfile = open("./lab_4_logs.txt",O_CREAT | O_WRONLY | O_TRUNC);
    if(logfile == -1){perror("File open error"); _exit(1);}
    close(logfile);

    sem_unlink("/mySemaphoreA");
    mySemaphoreA = sem_open("/mySemaphoreA", O_CREAT | O_EXCL, 0, 1);
    if (mySemaphoreA == SEM_FAILED)
    { 
        int err = errno;
        printf("semA_open fail: %s\n", strerror(err));
    }

    sem_unlink("/mySemaphoreB");
    mySemaphoreB = sem_open("/mySemaphoreB", O_CREAT | O_EXCL, 0, 1);
    if (mySemaphoreB == SEM_FAILED)
    { 
        int err = errno;
        printf("semB_open fail: %s\n", strerror(err));
    }
    args1.threadNum = 1;
    args1.sem1 = mySemaphoreA;
    args1.sem2 = mySemaphoreB;
    pthread_create(&thread_1, NULL, incr_counter, (void *)&args1);
    args2.threadNum = 2;
    args2.sem1 = mySemaphoreB;
    args2.sem2 = mySemaphoreA;
    pthread_create(&thread_2, NULL, incr_counter, (void *)&args2);

    pthread_join(thread_2, NULL);
    return 0;
}