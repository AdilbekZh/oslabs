#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t a_sem;
sem_t b_sem;
sem_t mutex;
sem_t barrier;

int count = 0;
int n = 2;


void *thread_1(void *vargp) {
	printf("A1\n");
	sem_post(&a_sem);
	sem_wait(&b_sem);
	printf("A2\n");

	sem_wait(&mutex);
	count++;
	sem_post(&mutex);

	if (count == n) sem_post(&barrier);

	sem_wait(&barrier);
	sem_post(&barrier);

	printf("Thread 1\n");

	pthread_exit(NULL);
}

void *thread_2(void *vargp) {
	printf("B1\n");
	sem_post(&b_sem);
	sem_wait(&a_sem);
	printf("B2\n");

	sem_wait(&mutex);
	count++;
	sem_post(&mutex);

	if (count == n) sem_post(&barrier);

	sem_wait(&barrier);
	sem_post(&barrier);

	printf("Thread 2\n");

	pthread_exit(NULL);
}


int main() {
	pthread_t tid1, tid2;

	sem_init(&a_sem, 0, 0);
	sem_init(&b_sem, 0, 0);
	sem_init(&mutex, 0, 1);
	sem_init(&barrier, 0, 0);
	printf("Hello from main thread! tid:%ld pid:%d\n", pthread_self(), getpid());
	pthread_create(&tid1, NULL, thread_1, NULL);
	pthread_create(&tid2, NULL, thread_2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

}