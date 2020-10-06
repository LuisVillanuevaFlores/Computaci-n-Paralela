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
int thread_count=4;
pthread_mutex_t barrier_mutex;

void* threadFn(void *id_ptr) {
    int thread_id = int id_ptr;
    srand(thread_id);
    int wait_sec = 1 + rand() % 10;
    printf("thread %d: Wait for %d seconds.\n", thread_id, wait_sec);
    this_thread::sleep_for(chrono::milliseconds(wait_sec) );
    printf("thread %d: Im ready...\n", thread_id);
    pthread_mutex_lock(&barrier_mutex);
    counter++;
    pthread_mutex_unlock(&barrier_mutex);
    while (counter < thread_count);
    printf("thread %d: Executing!\n", thread_id);
    return NULL;
}

int main() {
    int thread;
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