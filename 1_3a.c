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
    sem_acquire(&h);
    sem_acquire(&h);
    sem_signal(&o);
    sem_signal(&o);
    sem_acquire(&mutex);
    (*water)++;
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
        
    for(i = 0; i < 12; i++){
        printf(1, "hydrogen %d initializing\n", i);
        thread_create(hReady, 0);
    }
    for(i = 0; i < 6; i++){
        printf(1, "oxygen %d initializing\n", i);
        thread_create(oReady, &water);
    }
   
    while(wait()>=0) ;
        
    printf(1, "Water end: %d\n", water);
        
    exit();
        
}
