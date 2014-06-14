#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t t_1_sem;

void *thread_1(void *vargp) {
	//even thread_1 is sleeping , thread_2 will not be scheduled to run
	//as thread_1 is holding the semphore
	printf("Hello from 1st thread\n");
	sem_post(&t_1_sem);
	pthread_exit(NULL);
}

void *thread_2(void *vargp) {
	sem_wait(&t_1_sem);
	sleep(1);
	printf("Hello from 2nd thread\n");
	pthread_exit(NULL);
}

int main() {
	pthread_t tid1, tid2;

	sem_init(&t_1_sem, 0, 0);
	printf("Hello from main thread! tid:%ld pid:%d\n", pthread_self(), getpid());
	pthread_create(&tid1, NULL, thread_1, NULL);
	pthread_create(&tid2, NULL, thread_2, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

}