#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define M 10
#define N 5

sem_t mutex;
sem_t full_pot;
sem_t empty_pot;
int serving = 0;

void *savage_thread(void *vargp) {
	long tid = (long) vargp;
	while (1) {
		sem_wait(&mutex);
		if (serving == 0) {
			printf("Savage %ld hungry... wake up cook!\n", tid);
			sem_post(&empty_pot);
			sem_wait(&full_pot);
		}
		serving--;
		printf("Savage %ld eating... now in pot = %d\n", tid, serving);
		sem_post(&mutex);
		sleep(1);
	}
	pthread_exit(NULL);
}

void *cook_thread(void *vargp) {
	while (1) {
		sem_wait(&empty_pot);
		printf("Aaah! hungry-angry savage..\n");
		serving = M;
		printf("Cook cooking... now in pot = %d\n", serving);
		printf("Cook sleeping\n", serving);
		sem_post(&full_pot);
		
	}
	pthread_exit(NULL);
}

int main() {
	pthread_t tid1;
	pthread_t t[N];
	
	sem_init(&mutex, 0, 1);
	sem_init(&full_pot, 0, 0);
	sem_init(&empty_pot, 0, 0);
	printf("Hello from main thread! tid:%ld pid:%d\n", pthread_self(), getpid());
	pthread_create(&tid1, NULL, cook_thread, (void*)0);
	int i;
	for (i=0; i<N; i++) {
		pthread_create(&t[i], NULL, savage_thread, (void*)(i+1));
	}

	for (i=0; i < N; i++) {
		pthread_join(t[i], NULL);
	}
	pthread_join(tid1, NULL);
}