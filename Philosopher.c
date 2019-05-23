//Gabriel dos Santos Leite
//Questão 3

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5 // quantidade de filósofos
#define LEFT (i + N - 1) % N // filósofo a esquerda
#define RIGHT (i + 1) % N // filósofo a direita
#define THINKING 0 //estado pensantivo do filosofo
#define HUNGRY 1 //estado faminto do filosofo
#define EATING 2 //estado que demonstra o filosofo comendo

int state[N];
sem_t mutex;
sem_t s[N];

void eat(int i) // função para o demonstrar o filosofo comendo
{
  printf("O filósofo %d está comendo.\n", i);
  sleep(rand() % 3 + 1);
  printf("O filósofo %d terminou de comer.\n", i);
}

void think(int i)// função para o demonstrar o filosofo comendo
{
  printf("O filósofo %d está pensando.\n", i);
  sleep(rand() % 3 + 1);
  printf("O filósofo %d terminou de pensar.\n", i);
}
void test(i) //verifica o estado dos filosofos e tenta pegar os garfos depenendo da condição
{
  if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
  {
    state[i] = EATING;
    sem_post(&s[i]);
  }
}

void take_forks(int i) //pega os garfos ou bloqueia
{
  sem_wait(&mutex);
  state[i] = HUNGRY;
  test(i);
  sem_post(&mutex);
  sem_wait(&s[i]);
}

void put_forks(i) //devolve os garfos a mesa
{
  sem_wait(&mutex);
  state[i] = THINKING;
  test(LEFT);
  test(RIGHT);
  sem_post(&mutex);
}

void philosopher(void *i)//função que mantém os filosofos motivados a comer, equanto os outros pensão
{
  int *phil = (int *)i;
  while (1)
  {
    think(*phil);
    take_forks(*phil);
    eat(*phil);
    put_forks(*phil);
  }
}

int main()
{
  int phils[N]; //Id de cada filósofo
  int i;
  pthread_t thread_id[N];
  sem_init(&mutex, 0, 1);

  for (i = 0; i < N; i++)//inicializando semáforo
  {
    sem_init(&s[i], 0, 0);
  }

  for (i = 0; i < N; i++) //instanciando 5 filósofos
  {
    phils[i] = i;
    pthread_create(&thread_id[i], NULL, (void *)philosopher, &phils[i]);
  }

  for (i = 0; i < N; i++)
  {
    pthread_join(thread_id[i], NULL);
  }
}
