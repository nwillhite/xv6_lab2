nclude "semaphore.h"
#include "proc.h"
#include "x86.h"
#include "defs.h"
#include "types.h"
#include "memlayout.h"
#include "user.h"

void
sem_init(struct Semaphore *s, int val)
{
    &s->value = val;
      initlock(&s->lock, (char*)s);
        init_q(&s->q);

}

//this should be entirely atomic
void
sem_acquire(Semaphore *s)
{

  //get the lock
  acquire(&s->lock);

  //decrement sem value
  &s->value -= 1;

  //if no resources, wait to be woken
  if (&s->value < 0)
  {
    add_q(&s->lock);
    release(&s->lock);
    tsleep();
  }

  // release lock
  release(&s->lock);
}

//this should be entirely atomic
void sem_signal(Semaphore *s)
{
  //get the lock
  acquire(&s->lock);

  //increment sem value
  &s->value += 1;

  //release the lock
  release(&s->lock);

  //if waiting threads(s), wake one
  if (&s->value < 0)
  {
    twakeup(pop_q(&s->q));
  }

}
