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
pthread_mutex_t mutex;
pthread_cond_t cond_var;

void* threadFn(void *id_ptr) {
    int thread_id = (int)id_ptr;
    srand(thread_id);
    int wait_sec = 1 + rand() % 5;
    sprintf(print,"thread %d: Wait for %d seconds.\n", thread_id, wait_sec);
    cout<<print;
    this_thread::sleep_for(chrono::milliseconds(wait_sec) );
    printf(print,"thread %d: Im ready...\n", thread_id);

    pthread_mutex_lock(&mutex);
    counter++;
    if (counter == thread_count) {
        counter = 0;
        pthread_cond_broadcast(&cond_var);
        printf("Wake up!!\n");
    } else {
        while (pthread_cond_wait(&cond_var, &mutex) != 0);
    }
    pthread_mutex_unlock(&mutex);

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