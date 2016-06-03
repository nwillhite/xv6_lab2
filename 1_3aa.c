#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "semaphore.h"
#include "barrier.c"

Semaphore h, o, mutex;
int oxygen, hydrogen, water;
Barrier b;

int num_threads;

void hReady(void * arg) {
/*    sem_signal(&h);
    sem_acquire(&o);
*/

    printf(1, "%d acquiring mutex\n", getpid());
    sem_acquire(&mutex);
    hydrogen++;
    if (hydrogen >=2 && oxygen >= 1) {
        sem_signal(&h);
        sem_signal(&h);
        hydrogen--;
        sem_signal(&o);
        oxygen--;
    }
    else {
        printf(1, "%d signaling mutex\n", getpid());
        sem_signal(&mutex);
    }
    sem_acquire(&h);
    water++;
    printf(1, "%d waters now\n", water);

    barrier_wait(&b);
}

void oReady(void * arg) {
    //printf(1, "%d about to acquire two h's\n", getpid());
    sem_acquire(&mutex);
    oxygen++;

    if (hydrogen >= 2) {
        sem_signal(&h);
        sem_signal(&h);
        hydrogen -= 2;
        sem_signal(&o);
        oxygen--;
    }
    else {
        sem_signal(&mutex);
    }

    sem_acquire(&o);
    water++;
    printf(1, "%d waters now\n", water);

    barrier_wait(&b);
    sem_signal(&mutex);
/*
    sem_acquire(&h);
    sem_acquire(&h);
    printf(1, "%d about to signal an o\n", getpid());
    sem_signal(&o);
    printf(1, "%d about to get mutex\n", getpid());
    sem_acquire(&mutex);
    printf(1, "about to increment water\n");
    (*water)++;
    printf(1, "%d about to signal mutext\n", getpid());
    sem_signal(&mutex);

    */
}


int main(int argc, char * argv[]) {
    int i;
     
    num_threads = 0;
    // Problem 1
    water = 0;
    oxygen = 0;
    hydrogen = 0;
        
    sem_init(&h, 0);
    sem_init(&o, 0);
    sem_init(&mutex, 1);
    barrier_init(&b, 3);
    void *tid;    
    for(i = 0; i < 6; i++){
        tid = thread_create(hReady, 0);
        if (tid == 0) {
            printf(1, "create thread failed!\n");
        }
        num_threads++;
    }
    for(i = 0; i < 3; i++){
        tid = thread_create(oReady, &water);  
        if (tid == 0) {
            printf(1, "create thread failed!\n");
        }
        num_threads++;
    }
 

    while(num_threads > 0) {
        texit();
    }
        
    printf(1, "Water end: %d\n", water);
        
    exit();
} 
