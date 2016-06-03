#include "types.h"
#include "user.h"
#include "semaphore.h"

int numCan, numMiss;
Semaphore mutex, cannibal, missionary, row;

void RowBoat() {
    printf(1, "Rowing!\n");
}

void CannibalArrives(void *arg) {
    sem_acquire(&mutex);
    if (numCan == 2) {
        numCan -= 2;
        sem_signal(&mutex);
        sem_signal(&cannibal);
        sem_signal(&cannibal);
    }
    else if (numMiss == 2) {
        numMiss -= 2;
        sem_signal(&mutex);
        sem_signal(&missionary);
        sem_signal(&missionary);
    }
    else {
        numCan++;
        sem_signal(&mutex);
        sem_acquire(&cannibal);
        sem_acquire(&row);
        return;
    }
    RowBoat();
    sem_signal(&row);
    sem_signal(&row);

}


void MissionaryArrives(void *arg) {
    sem_acquire(&mutex);
    if (numMiss == 2) {
        numMiss -= 2;
        sem_signal(&mutex);
        sem_signal(&missionary);
        sem_signal(&missionary);
    }
    else if (numMiss == 1 && numCan == 1) {
        numMiss -= 2;
        numCan--;
        sem_signal(&mutex);
        sem_signal(&missionary);
        sem_signal(&cannibal);
    }
    else {
        numMiss++;
        sem_signal(&mutex);
        sem_acquire(&missionary);
        sem_acquire(&row);
        return;
    }
    RowBoat();
    printf(1, "signaling row\n");
    sem_signal(&row);
    printf(1, "signaling row\n");
    sem_signal(&row);

}

int main() {
    numCan = numMiss = 0;

    sem_init(&mutex, 1);
    sem_init(&cannibal, 0);
    sem_init(&missionary, 0);
    sem_init(&row, 0);

    int i;
    void *tid;
    for (i = 0; i < 20; i++) {
        if (i % 2) {
            tid = thread_create(CannibalArrives, (void*)0);
            if (tid == 0) {
                printf(1, "failed to create thread!\n");
            }
        }
        else {
            tid = thread_create(MissionaryArrives, (void*)0);
            if (tid == 0) {
                printf(1, "failed to create thread!\n");
            }
        }
    }

    while(wait()>=0);

    exit();
}
