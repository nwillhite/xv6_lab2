#include "types.h"
#include "param.h"
#include "semaphore.h"

typedef struct Barrier {
    int n; //number of threads needed to open barrier
    int count;
    Semaphore mutex, turnstile, turnstile2;
} Barrier;

void barrier_init(Barrier* b, int n) {
    b->n = n;
    b->count = 0;
    printf(1, "init barrier mutex\n");
    sem_init(&b->mutex, 1);
    printf(1, "init barrier turnstile\n");
    sem_init(&b->turnstile, 0);
    printf(1, "init barrier turnstile2\n");
    sem_init(&b->turnstile2, 0);
}

void barrier_phase1(Barrier *b) {
    sem_acquire(&b->mutex);
    b->count++;
    if (b->count == b->n) {
        int i;
        for (i = 0; i < b->n; i++) {
            sem_signal(&b->turnstile);
        }
    }
    sem_signal(&b->mutex);
    sem_acquire(&b->turnstile);
}

void barrier_phase2(Barrier *b) {
    sem_acquire(&b->mutex);
    b->count--;
    if (b->count == 0) {
        int i;
        for (i = 0; i < b->n; i++) {
            sem_signal(&b->turnstile2);
        }
    }
    sem_signal(&b->mutex);
    sem_acquire(&b->turnstile2);
}

void barrier_wait(Barrier *b) {
    barrier_phase1(b);
    barrier_phase2(b);
}
