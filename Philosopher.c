#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];
sem_t mutex;
sem_t s[N];

void eat(int i)
{
  printf("O filósofo %d está comendo.\n", i);
  sleep(rand() % 3 + 1);
  printf("O filósofo %d terminou de comer.\n", i);
}

void think(int i)
{
  printf("O filósofo %d está pensando.\n", i);
  sleep(rand() % 3 + 1);
  printf("O filósofo %d terminou de pensar.\n", i);
}
void test(i)
{
  if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
  {
    state[i] = EATING;
    // sem_post(&s[i]);
  }
}

void take_forks(int i)
{
  // sem_wait(&mutex);
  state[i] = HUNGRY;
  test(i);
  // sem_post(&mutex);
  // sem_wait(&s[i]);
}

void put_forks(i)
{
  // sem_wait(&mutex);
  state[i] = THINKING;
  test(LEFT);
  test(RIGHT);
  // sem_post(&mutex);
}

void philosopher(void *i)
{
  int *phil = (int *)i;
  while (1)
  {
    think(*phil);
    take_forks(*phil);
    eat(*phil);
    put_forks(*phil);
  }

  pthread_exit((void *)0);
}

int main()
{
  int phils[N];
  int i;
  pthread_t thread_id[N];
  // sem_init(&mutex, 0, 1);

  // for (i = 0; i < N; i++)
  // {
  //   sem_init(&s[i], 0, 0);
  // }

  for (i = 0; i < N; i++)
  {
    phils[i] = i;
    pthread_create(&thread_id[i], NULL, (void *)philosopher, &phils[i]);
  }

  for (i = 0; i < N; i++)
  {
    pthread_join(thread_id[i], NULL);
  }
}
