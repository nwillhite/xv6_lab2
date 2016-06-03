#include "types.h"
#include "user.h"
#include "semaphore.h"

Semaphore *h, *o;
int water_molecules;
Semaphore *mutex;

void hReady(void *arg) {
    sem_signal(h);
    sem_acquire(o);
}

void oReady(void *h2o) {
    int *w = (int*)h2o;
    sem_acquire(h);
    sem_acquire(h);
    (*w)++;
    sem_signal(o);
    sem_signal(o);
    sem_acquire(mutex);
    water_molecules+=1;
    sem_signal(mutex);
}

int main() {
   
    printf(1, "starting\n");
    sem_init(h, 0);
    sem_init(o, 0);
    sem_init(mutex, 1);

    int i;

    water_molecules = 0;

    printf(1, "Num of H20's: %d\n", water_molecules);

    for (i = 0; i < 36; i++) {
        if (i%3) thread_create(hReady, 0);
        else thread_create(oReady, &water_molecules);
    }

    while (wait() >= 0) ;
    
    printf(1, "Num of H20's: %d\n", water_molecules);
    
    exit();
}
