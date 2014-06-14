#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define M	5
#define K 5
#define N 3

struct thread_data
{
  int thread_id;
  int i;
  int j;
};

int a[M][K];
int b[K][N];
int c[M][N];
struct thread_data thread_data_arr[M*N];


void *calculate(void *threadarg)
{
   struct thread_data *my_data;
   my_data = (struct thread_data *) threadarg;
   int i = my_data->i;
   int j= my_data->j;
   int l;
   for (l=0; l<K; l++) {
    c[i][j] += a[i][l] * b[l][j];
   }
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[M][N];

int i, j;

for (i=0; i<M; i++){
  for (j=0; j<K; j++) {
    a[i][j] = 1;
  }
}

for (i=0; i<K; i++){
  for (j=0; j<N; j++) {
    b[i][j] = 2;
  }
}

for (i=0; i<M; i++){
  for (j=0; j<K; j++) {
    printf("%d ", a[i][j]);;
  }
  printf("\n");
}
printf("------------------------\n");
for (i=0; i<K; i++){
  for (j=0; j<N; j++) {
    printf("%d ", b[i][j]);;
  }
  printf("\n");
}
printf("------------------------\n");
for (i=0; i<M; i++)
  for (j=0; j<N; j++) {
    //c[i][j] = (int *) malloc(sizeof(int));
    thread_data_arr[i*M + j].thread_id = i*M + j;
    thread_data_arr[i*M + j].i = i;
    thread_data_arr[i*M + j].j = j;
    pthread_create(&threads[i][j], NULL, calculate, (void *)&thread_data_arr[i*M + j]);
  }
for (i=0; i<M; i++)
  for (j=0; j<N; j++) {
    pthread_join(threads[i][j], NULL);
}
for (i=0; i<M; i++){
  for (j=0; j<N; j++) {
    printf("%d ", c[i][j]);;
  }
  printf("\n");
}
pthread_exit(NULL);
}