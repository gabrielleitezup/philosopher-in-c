#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (1 + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef int semaphore;
int state[N];
sem_t mutex;
sem_t s[N];

// semaphore mutex = 1;
// semaphore s[N];

void eat()
{
  printf("O filósofo está comendo.\n");
  sleep(0);
}

void think()
{
  printf("O filósofo está pensando.\n");
  sleep(1);
}
void test(i)
{
  if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
  {
    state[i] = EATING;
    sem_post(&s[i]);
  }
}

void take_forks(int i)
{
  sem_wait(&mutex);
  state[i] = HUNGRY;
  test(i);
  sem_post(&mutex);
  sem_wait(&s[i]);
}

void put_forks(i)
{
  sem_wait(&mutex);
  state[i] = THINKING;
  test(LEFT);
  test(RIGHT);
  sem_post(&mutex);
}

void philosopher(int i)
{
  while (1)
  {
    think();
    take_forks(i);
    eat();
    put_forks(i);
  }
}

int main()
{
  int phils[N];
  int i;
  pthread_t thread_id[N];

  sem_init(&mutex, 0, 1);

  for (i = 0; i < N; i++)
  {
    sem_init(&s[i], 0, 0);
  }

  for (i = 0; i < N; i++)
  {
    pthread_create(&thread_id[i], NULL, (void*)philosopher, &phils[i]);
    printf("Philosopher %d is thinking\n", i + 1);
  }

  for (i = 0; i < N; i++)
  {
    pthread_join(thread_id[i], 0);
  }
}
