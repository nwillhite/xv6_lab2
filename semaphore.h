#include "param.h"
#include "queue.h"
#include "spinlock.h"

typedef struct Semaphore {
    int value;
    struct queue *q;
    struct spinlock lock;
}Semaphore;

//functions
void sem_init(struct Semaphore *s, int val);
void sem_acquire(Semaphore *s);
void sem_signal(Semaphore *s);


