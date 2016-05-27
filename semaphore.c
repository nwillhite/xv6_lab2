#include "types.h"
#include "stat.h"
#include "user.h"
//#include "defs.h"
#include "semaphore.h"
#include "queue.h"

void
sem_init(struct Semaphore *s, int val)
{
  s->value = val;
  //lock_init(&s->lock);
  initlock(&s->lock, (char*)s);
  s->q = (struct queue*)malloc(sizeof(struct queue));
  init_q(s->q);
  printf(1, "queue done\n");
}


//this should be entirely atomic
void
sem_acquire(struct Semaphore *s)
{
    //get the lock
    //lock_acquire(&s->lock);
    acquire(&s->lock);

    //decrement sem value
    s->value -= 1;

    //if no resources, wait to be woken
    if (s->value < 0) 
    {
        int pid;
        pid = getpid();
        add_q(s->q, pid);
        //lock_release(&s->lock);
        release(&s->lock);
        tsleep();
    } 
    else 
    {
        //release lock
        //lock_release(&s->lock);
        release(&s->lock);
    }
} 


//this should be entirely atomic
void
sem_signal(struct Semaphore *s)
{
    //get the lock
    //lock_acquire(&s->lock);
    acquire(&s->lock);

    //increment sem value
    s->value += 1;
 
    //if waiting thread(s), wake one
    if (s->value < 0)
    {
        twakeup(pop_q(s->q));
    }
    
    //relaese the lock
    //lock_release(&s->lock); 
    release(&s->lock);
}
 
