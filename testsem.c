#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "semaphore.h"

Semaphore H, hRdy, O;

void hReady(void * arg) {
    sem_acquire(&H);
    sem_signal(&hRdy);
}

void oReady(void * w) {
    int * water = (int*)w;
    sem_acquire(&O);
    sem_acquire(&hRdy);
    sem_acquire(&hRdy);
    (*water)++;
    sem_signal(&O);
    sem_signal(&H);
    sem_signal(&H);

}

int main(int argc, char * argv[]) {
    int i, water;

    // Problem 1
    water = 0;
    printf(1, "Water begin: %d\n", water);
        
    sem_init(&H, 2);
    sem_init(&hRdy, 0);
    sem_init(&O, 1);
        
    for(i = 0; i < 12; i++)
    thread_create(hReady, 0);
    for(i = 0; i < 6; i++)
    thread_create(oReady, &water);
        
    while(wait()>=0) ;
        
    printf(1, "Water end: %d\n", water);
        
    exit();
        
}
