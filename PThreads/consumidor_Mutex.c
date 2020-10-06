#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;
#define MSG_MAX 20
char* messages[20];
pthread_mutex_t mutex_p;

void* Send_msg(void* rank){
	long my_rank = (long) rank;
	long dest = (my_rank + 1) % thread_count;
	long source = (my_rank + thread_count - 1) % thread_count;
	char* my_msg = malloc(MSG_MAX * sizeof(char));

	sprintf(my_msg, "Hello to %ld from %ld", dest, my_rank);

	pthread_mutex_lock(&mutex_p);
	messages[dest] = my_msg;

	if(messages[my_rank] != NULL)
		printf("Thread %ld > %s\n", my_rank, messages[my_rank]);
	else
		printf("Thread %ld > No message from %ld\n", my_rank, source);

	pthread_mutex_unlock(&mutex_p);

	return NULL;
}

int main(int argc, char* argv[]) {
	pthread_mutex_init(&mutex_p, NULL);
	long thread; /* Use long in case of a 64−bit system */
	pthread_t* thread_handles;

	/* Get number of threads from command line */
	thread_count = strtol(argv[1], NULL, 10);

	thread_handles = malloc (thread_count * sizeof(pthread_t));

	for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], NULL, Send_msg, (void*) thread);

	for (thread = 0; thread < thread_count; thread++)
		pthread_join(thread_handles[thread], NULL);

	pthread_mutex_destroy(&mutex_p);
	free(thread_handles);
	return 0;
}