#ifndef __SEM_H
#define __SEM_H

//#include "param.h"
#include "queue.h"
#include "spinlock.h"

typedef struct Semaphore{
    int value;
    struct queue *q;
    //lock_t lock;
    struct spinlock lock;
}Semaphore;

void sem_init(struct Semaphore*, int);
void sem_acquire(struct Semaphore*);
void sem_signal(struct Semaphore*);

//functions
/*
void
sem_init(struct Semaphore *s, int val)
{
  s->value = val;
  //lock_init(&s->lock);
  initlock(&s.lock, (char*)s);
  s->q = malloc(sizeof(struct queue));
  init_q(s->q);
  printf(1, "queue done\n");
}


//this should be entirely atomic
void
sem_acquire(Semaphore *s)
{
    //get the lock
    //lock_acquire(&s->lock);
    acquire(&s.lock);

    //decrement sem value
    s->value -= 1;

    //if no resources, wait to be woken
    if (s->value < 0) 
    {
        int pid;
        pid = getpid();
        add_q(s->q, pid);
        //lock_release(&s->lock);
        release(&s.lock);
        tsleep();
    } 
    else 
    {
        //release lock
        //lock_release(&s->lock);
        release(&s.lock);
    }
} 


//this should be entirely atomic
void
sem_signal(Semaphore *s)
{
    //get the lock
    //lock_acquire(&s->lock);
    acquire(&s.lock);

    //increment sem value
    s->value += 1;
 
    //if waiting thread(s), wake one
    if (s->value < 0)
    {
        twakeup(pop_q(s->q));
    }
    
    //relaese the lock
    //lock_release(&s->lock); 
    release(&s.lock);
}
 */       
#endif // __SEM_H
