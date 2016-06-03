#include "types.h"
#include "param.h"
#include "defs.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
//#include "queue.h"
#include "semaphore.h"
//comment``
void
sem_init(struct Semaphore *s, int val)
{
  s->value = val;
  //lock_init(&s->lock);
  initlock(&s->lock, (char*)s);
  s->q_front = s->q_back = 0;
  int i;
  for (i = 0; i < NPROC; i++) {
      s->q[i] = 0;
  }
  s->wakeups = 0;
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
/*
    //if no resources, wait to be woken
    if (s->value < 0) 
    {
        int pid;
        pid = proc->pid;
        //add_q(s->q, pid);
        //cprintf("%d joining queue\n", pid);
        s->q[s->q_back] = pid;
        s->q_back = ((s->q_back + 1) % NPROC);
        //lock_release(&s->lock);
        //cprintf("%d going to sleep\n", pid);
        release(&s->lock);
        tsleep();
    } 
    else 
    {
        //release lock
        //lock_release(&s->lock);
        //cprintf("%d releasing lock\n", proc->pid);
        release(&s->lock);
        //cprintf("%d released the lock\n", proc->pid);
    }
*/
    if (s->value < 0) {
        int pid;
//        release(&s->lock);
        do {
            pid = proc->pid;
            s->q[s->q_back] = pid;
            s->q_back = ((s->q_back + 1) % NPROC);
            sleep(&s, &s->lock);
        } while (s->wakeups < 1);
//        acquire(&s->lock);
        s->wakeups--;
    }
    release(&s->lock);
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
 /*   if (s->value < 0)
    {
        int pid;
        pid = s->q[s->q_front];
        s->q[s->q_front] = 0;
        s->q_front += ((s->q_front + 1) % NPROC);
        //cprintf("%d waking up %d\n", proc->pid, pid);
        twakeup(pid);
    }
    
    //relaese the lock
    //lock_release(&s->lock); 
    //cprintf("%d is about to release the lock sem.c\n", proc->pid);
    release(&s->lock);
    //cprintf("%d has just released the lock\n", proc->pid);
*/
    if (s->value <= 0) {
        int pid;
        pid = s->q[s->q_front];
        s->q[s->q_front] = 0;
        s->q_front += ((s->q_front +1) % NPROC);
        s->wakeups++;
        twakeup(pid);
    }
    release(&s->lock);

}
 






