#include "types.h"
#include "stat.h"
#include "param.h"
#include "defs.h"
#include "semaphore.h"
#include "mmu.h"
#include "queue.h"
#include "x86.h"
#include "proc.h"
//comment``
void
sem_init(struct Semaphore *s, int val)
{
  s->value = val;
  //lock_init(&s->lock);
  initlock(&s->lock, (char*)s);
  cprintf("queue done\n");
  s->q_front = s->q_back = 0;
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
        pid = proc->pid;
        //add_q(s->q, pid);
        s->q[s->q_back] = pid;
        s->q_back = ((s->q_back + 1) % NPROC);
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
        int pid;
        pid = s->q[s->q_front];
        s->q_front += ((s->q_front + 1) % NPROC);
        twakeup(pid);
    }
    
    //relaese the lock
    //lock_release(&s->lock); 
    release(&s->lock);
}
 
