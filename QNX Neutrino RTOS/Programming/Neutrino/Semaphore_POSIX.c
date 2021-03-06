#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/neutrino.h>
#include <semaphore.h>


sem_t Semaphore;


void* Thread1 (void* args)
{
	printf("%d: entering\n", pthread_self());
	printf("%d: doing down on semaphore now\n", pthread_self());
	// if(sem_trywait(&Semaphore) == EAGAIN)
	//    printf("%d: semaphore already locked\n", pthread_self());
	sem_wait(&Semaphore);
	printf("%d: unblocked from semaphore\n", pthread_self());
	
	return NULL;
}

void* Thread2 (void* args)
{
	printf("%d: entering\n", pthread_self());
	printf("%d: doing up on semaphore now\n", pthread_self());
	sem_post(&Semaphore);
	printf("%d: did up on semaphore\n", pthread_self());
	
	return NULL;
}

int main()
{
	SchedSet(NULL, NULL, SCHED_RR, NULL);
	sem_init(&Semaphore, 1, 1);			// creates an named ("1") semaphore with initail count "1"
	
	ThreadCreate(NULL, Thread1, NULL, NULL);
	ThreadCreate(NULL, Thread1, NULL, NULL);
	sleep(3);
	ThreadCreate(NULL, Thread2, NULL, NULL);
	SchedYield();
			
	sleep(11);
	return(0);
}