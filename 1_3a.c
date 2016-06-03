#include "semaphore.h"
#include "user.h"
#define TEST_NUM 21

Semaphore h, o, mutex;
int water;

void hReady(void * arg);
void oReady(void * arg); 

int main(int argc, char * argv[]) {
    int i;
     
    // Problem 1
    water = 0;
    



    sem_init(&h, 0);
    sem_init(&o, 0);
    sem_init(&mutex, 1);
    void *tid;    
    for (i = 0; i < TEST_NUM; i++)
        if (i % 3){ 
            tid = thread_create(hReady, 0);
            if (tid == 0) {
                printf(1, "create thread failed!\n");
         }
         else {
            tid = thread_create(oReady, 0);
            if (tid == 0) {
                 printf(1, "create thread failed!\n");
             }
         }
    }
    for(i = 0; i < 3; i++){
        tid = thread_create(oReady, 0);  
        if (tid == 0) {
            printf(1, "create thread failed!\n");
        }
    }
 
    while(wait()>0);
    printf(1, "Water end: %d\n", water);
        
    exit();
}
void hReady(void * arg) {
    sem_acquire(&h);
    sem_signal(&o);
    texit();
}

void oReady(void * arg) {
 
    sem_signal(&h);    
    sem_signal(&h);    
    sem_acquire(&o);    
    sem_acquire(&o);    

    sem_acquire(&mutex);
    water++;
    sem_signal(&mutex); 
    
    
    texit();
}


 
