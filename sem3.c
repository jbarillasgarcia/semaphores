#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define HOW_MANY 10
#define MY_RANDOM 10

// declaramos nuestro semáforo
sem_t mutex;

/*
* Esta función contiene las instrucciones que ejecutará el hilo Hola mundo
*/
void *saludar(void *arg)
{
	int count = 1;

	for (int i = 0; i < HOW_MANY; i++) {
		// esperar hasta que el semáforo nos permita continuar o bloquear el semáforo
		sem_wait(&mutex);

		// sección crítica
		FILE *myFile;
		myFile = fopen("/home/jbarillas/Umg/outputFiles/sem3_output.txt", "a");
		if (myFile != NULL) {
			fprintf(myFile, "Saludar #%d\n", count++);
			fclose(myFile);
		}

		// desbloquear el semáforo
		sem_post(&mutex);

		sleep(rand() % MY_RANDOM);
	}
}

/*
* Esta función contiene las instrucciones que ejecutará el hilo Adios
*/
void *despedir(void *arg)
{
	int count = 1;

	for (int i = 0; i < HOW_MANY; i++) {
		// esperar hasta que el semáforo nos permita continuar o bloquear el semáforo
		sem_wait(&mutex);	

		// sección crítica
		FILE *myFile;
                myFile = fopen("/home/jbarillas/Umg/outputFiles/sem3_output.txt", "a");
                if (myFile != NULL) {
                        fprintf(myFile, "Despedir #%d\n", count++);
                        fclose(myFile);
                }

		// desbloquear el semáforo
		sem_post(&mutex);

		sleep(rand() % MY_RANDOM);
	}
}


/*
* Esta es la función principal de nuestro programa.
*/
int main()
{	
	// inicializamos nuestro generador de números aleatorios
	srand(time(NULL));

	// inicializamos nuestro semáforo
	sem_init(&mutex, 0, 1);

	// declaramos dos hilos
	pthread_t t1;
	pthread_t t2;

	// inicializamos el primer hilo
	pthread_create(&t1, NULL, saludar, NULL);

	// inicializamos el segundo hilo
	pthread_create(&t2, NULL, despedir, NULL);

	// indicamos al hilo principal que espere hasta que nuestros dos hilos terminen de ejecutarse.
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	// destruimos nuestro semáforo
	sem_destroy(&mutex);

	return 0;
}
