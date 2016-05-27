#include "types.h"
#include "stat.h"
#include "user.h"
//#include "thread.c"
#include "semaphore.h"

struct thread{
    int tid;
};

struct{
    lock_t lock;
    struct thread threads[64];
    int total;
}ttable;

struct Semaphore sem;

void func(void *arg_ptr);


int main(){
    struct thread *t;
    printf(1, "initializing semaphore\n");
    sem_init(&sem, 1);
    printf(1, "done initializing\n");
    int i;
    printf(1, "init ttable\n");
    lock_init(&ttable.lock);
    ttable.total = 0;

    lock_acquire(&ttable.lock);
    for (t=ttable.threads; t<&ttable.threads[64]; t++){
        t->tid = 0;
    }
    lock_release(&ttable.lock);
    printf(1, "testing semaphores \n\n\n");
    for (i = 0; i < 10; i++) {
        thread_create(func, 0);
    }

    i = 0;

    while (ttable.total > 0){
        printf(1, "total threads: %d", ttable.total);
        texit();
        ttable.total--;
    }
    exit();


}

void func(void *arg_ptr) {
    int tid;
    tid = getpid();
    lock_acquire(&ttable.lock);
    (ttable.threads[ttable.total]).tid = tid;
    ttable.total++;
    lock_release(&ttable.lock);

 //   printf(1, "Thread %d, getting semaphore.\n", tid);
    sem_acquire(&sem);
    printf(1, "%d has the semaphore!\n", tid);
    sem_signal(&sem);
    texit();
}
