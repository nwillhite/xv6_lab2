#include "semaphores.h"

void thread_test(void * arg_ptr)
{
  printf(1, "Yielding thread.\n");
  thread_yield();
  printf(1, "Exit yielding...\n");
  texit();
}

int main()
{

  printf(1, "Thread_yield test: creating threads for testing...\n");
  void * thread1 = thread_create(thread_test, (void*) 0);

  if(thread1 == 0)
  {
    printf(1, "thread_create has failed.\n")
    exit();
  }
  
  void * thread2 = thread_create(thread_test, (void*) 0);

  if (thread2 == 0)
  {
    printf(1, "thread_create has failed.\n");
    exit();
  }

  void * thread3 = thread_create(thread_test, (void*) 0);

  if (thread3 == 0)
  {
    printf(1, "thread_create has  failed.\n");
    exit();
  }

  void * thread4 = thread_create(thread_test, (void*) 0);

  if (thread4 == 0)
  {
    printf(1, "thread_create has failed.\n");
    exit();
  }

  while(wait() > 0);
  printf(1, "All threads have yield properly.\n");
  exit();
  return 0;

}
