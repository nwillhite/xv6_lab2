#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "semaphore.h"

Semaphore h, o, mutex;

void hReady(void * arg) {
    sem_signal(&h);
    sem_acquire(&o);
}

void oReady(void * w) {
    int *water = (int*)w;
    printf(1, "%d about to acquire two h's\n", getpid());
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
}

int main(int argc, char * argv[]) {
    int i, water;

    // Problem 1
    water = 0;
    printf(1, "Number of H20 at start: %d\n", water);
        
    sem_init(&h, 0);
    printf(1, "h has finished\n");
    sem_init(&o, 0);
    printf(1, "o has finished\n");
    sem_init(&mutex, 1);
    printf(1, "mutex has finished\n");
        
    for(i = 0; i < 6; i++){
        printf(1, "hydrogen %d initializing\n", i);
        thread_create(hReady, 0);
    }
    for(i = 0; i < 3; i++){
        printf(1, "oxygen %d initializing\n", i);
        thread_create(oReady, &water);
    }
   
    while(wait()>=0) ;
        
    printf(1, "Water end: %d\n", water);
        
    exit();
        
}
