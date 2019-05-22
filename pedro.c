#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define ESQUERDA (idFil + 4) % 5
#define DIREITA (idFil + 1) % 5
#define PENSANDO (0)
#define FAMINTO (1) 
#define COMENDO (2)

sem_t mutex;
sem_t mux_fil[5];
int estado[5];

void intencao(int idFil){

	if(estado[ESQUERDA] != COMENDO && estado[DIREITA] != COMENDO && estado[idFil] == FAMINTO){
		estado[idFil] = COMENDO;
		printf("Filosofo %d esta comendo \n",idFil+1);
  	sem_post(&(mux_fil[idFil]));
	}

}

void deixarGarfo(int idFil)
{
	sem_wait(&mutex);
	estado[idFil]= PENSANDO;
	printf("Filosofo %d esta pensando \n",idFil+1);
	intencao(ESQUERDA);
 	intencao(DIREITA);
	sem_post(&mutex);

}

void pegarGarfo(int idFil)
{
	sem_wait(&mutex);
	estado[idFil] = FAMINTO;
	intencao(idFil);
	sem_post(&mutex);
	sem_wait(&(mux_fil[idFil]));
}

void * filosofo(void* idFil){

	int *id = (int *)idFil;

	while(1)
  {
		pegarGarfo(*(id));
		sleep(rand() % 10 + 1);
		deixarGarfo(*(id));
		sleep(rand() % 10 + 1);
}
	pthread_exit((void*)0);
}

int main ()
{
	pthread_t f1,f2,f3,f4,f5;
	sem_init(&mutex, 0, 1);
  int a=0, b=1,c=2, d=3, e=4, i;

	for(i=0;i<5;i++)
			sem_init(&mux_fil[i], 0, 0);
  
	pthread_create(&f1,NULL,filosofo,(void*) & (a));
  pthread_create(&f2,NULL,filosofo,(void*) & (b));
  pthread_create(&f3,NULL,filosofo,(void*) & (c));
  pthread_create(&f4,NULL,filosofo,(void*) & (d));
  pthread_create(&f5,NULL,filosofo,(void*) & (e));		
  
  pthread_join(f1,NULL);
  pthread_join(f2,NULL);
	pthread_join(f3,NULL);
	pthread_join(f4,NULL);
	pthread_join(f5,NULL);
}
