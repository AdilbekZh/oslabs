#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t sem;
int count = 0;

void *thread_1(void *vargp) {
	sem_wait(&sem);
	count++;
	printf("Thread 1 count = %d\n", count);
	sem_post(&sem);
	pthread_exit(NULL);
}

void *thread_2(void *vargp) {
	sem_wait(&sem);
	count++;
	printf("Thread 2 count = %d\n", count);
	sem_post(&sem);
	pthread_exit(NULL);
}

int main() {
	pthread_t tid1, tid2;

	sem_init(&sem, 0, 1);
	printf("Hello from main thread! tid:%ld pid:%d\n", pthread_self(), getpid());
	pthread_create(&tid1, NULL, thread_1, NULL);
	pthread_create(&tid2, NULL, thread_2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

}