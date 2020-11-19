#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>

static sem_t* mySemaphore;

void incr_counter(int threadNum) {
    int counter = 0;
    int i=0;
    do {
        sleep(1);
        counter++;
        sem_wait(mySemaphore);
        int logfile = open("./lab_4_logs.txt", O_WRONLY | O_APPEND);

        if(logfile == -1){perror("File open error"); return 1;}
        dprintf(logfile, "Thread %d counter %d\n", threadNum, counter);
        printf("Thread %d counter %d\n", threadNum, counter);
        sleep(1);

        close(logfile);
        sem_post(mySemaphore);
    } while ( i<5 );
}

int main(int argc, char ** argv) {
    pthread_t thread_1;
    pthread_t thread_2;
    sem_unlink("/mySemaphore");
    mySemaphore = sem_open("/mySemaphore", O_CREAT | O_EXCL, 0, 1);
    if (mySemaphore == SEM_FAILED)
    { 
        int err = errno;
        printf("sem_open fail: %d\n", strerror(err));
    }

    pthread_create(&thread_1, NULL, incr_counter, 1);
    pthread_create(&thread_2, NULL, incr_counter, 2);

    pthread_join(thread_2, NULL);
    return 0;
}