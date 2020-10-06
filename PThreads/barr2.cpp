#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <semaphore.h>
#define THREAD_COUNT 8
using namespace std;


int counter=0;
int thread_count=8;
sem_t count_sem;
sem_t barrier_sem;

void* threadFn(void *id_ptr) {
    int thread_id = (int)id_ptr;
    srand(thread_id);
    int wait_sec = 1 + rand() % 10;
    printf("thread %d: wait for %d seconds.\n", thread_id, wait_sec);
    this_thread::sleep_for(chrono::milliseconds(wait_sec) );
    printf("thread %d: Im ready...\n", thread_id);
    sem_wait(&count_sem);
    if (counter == thread_count-1) {
        counter = 0;
        sem_post(&count_sem);
        for (int j = 0; j < thread_count-1; j++)
            sem_post(&barrier_sem);
    } else {
        counter++;
        sem_post(&count_sem);
        sem_wait(&barrier_sem);
    }
    printf(print,"thread %d: Executing!\n", thread_id);
    return NULL;
}

int main() {
    int thread;
    char print[100];
    pthread_t ids[THREAD_COUNT];

    for (thread=0; thread < THREAD_COUNT; thread++) {
        pthread_create(&ids[thread], NULL, threadFn, (void*) thread);
    }
    printf(print,"main() is ready.\n");
    for (thread=0; thread < THREAD_COUNT; thread++) {
        pthread_join(ids[thread], NULL);
    }

    return 0;
}