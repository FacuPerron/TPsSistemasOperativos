#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <semaphore.h>

union semun{
	int val ;
	struct semid_ds *buf;
	ushort *array;
	struct seminfo *__buf;
	void *__pad;
};


void down(int semid, int id, int recursos);
void up(int semid, int id, int recursos);

int main() {
	
	// Imprimimos nuestros nombres
	printf("Año 2023, 2C. Grupo n° 44.\n");
	printf("Integrantes: Perrón Facundo, perronfacundo2015@gmail.com\n");
	printf("Manuel Calvo, mancalvo@frsf.utn.edu.ar\n");
	printf("Valentino Delarmelina, valentinodelarmelina@outlook.com\n\n");	

	// Definimos clave y buffer para utilizacion en memoria compartida
	key_t claveMem = ftok(".", 'a');
	int shmid;
	if((shmid = shmget(claveMem, sizeof(char)*23, IPC_CREAT | 0660)) == -1) {
		perror("Problema con shmget");
		return -1;
	}

	char *buffer = shmat(shmid, 0, 0);

	// Definimos semaforos
	key_t claveSems;
	int semid;
	if((claveSems = ftok(".", 'z')) == -1) {
		perror("Problema con ftok");
		exit(1);
	}
	if((semid = semget(claveSems, 2, 0666|IPC_CREAT)) == -1) {
		perror("Problema con semget");
		exit(1);
	}
	union semun value;

	// Mutex para alternancia entre procesos (clubes)
	value.val = 1;

	if(( semctl(semid, 0, SETVAL, value)) == -1) {
		perror("Problema con semctl");
		exit(1);
	}

	// Semaforo para sincronizar finalizacion de procesos con el proceso padre
	value.val = 2;
	if(( semctl(semid, 1, SETVAL, value)) == -1) {
		perror("Problema con semctl:");
		exit(1);
	}

	// Creacion de procesos hijos
	pid_t club2;
	pid_t club1 = fork();

	if(club1 != 0) {
		club2 = fork();
	} 

	if(club1 == 0) {	// Ingresa al condicional solo el proceso club1
		down(semid, 1, 1); // Realizamos un down del semaforo para bloquear el proceso padre hasta que los clubes finalicen
		char bandera_club[9] = "ROJAMAAZU";
		// Se realiza un down de mutex, se agrega sobre el buffer compartido las tres letras que representan cada color
		// Luego, se realiza un up del mutex y se duerme el proceso durante un instante, para evitar que vuelva sobre
		// el iterador y tome nuevamente el down de mutex antes que el club2.
		for(int i = 0; i < 3; i++) {
			down(semid, 0, 1);
			printf("Imprimiendo color del primer club...\n");
			sleep(1);
			buffer[(2*i*4)]     = bandera_club[3*i];
			buffer[(2*i*4) + 1] = bandera_club[3*i+1];
			buffer[(2*i*4) + 2] = bandera_club[3*i+2];
			buffer[(2*i*4) + 3] = '-';
			printf("COLOR IMPRESO: %c%c%c\n", bandera_club[3*i], bandera_club[3*i+1], bandera_club[3*i+2]);
			up(semid, 0, 1);
			usleep(1);
		}
		// Se hace un up del semaforo que bloquea al proceso padre
		up(semid, 1, 1);
		return 0;
	}
	// Idem club1, pero con club2
	if(club2 == 0) {
		down(semid, 1, 1);
		char bandera_club[9] = "NARVERVIO";
		for(int i = 0; i < 3; i++) {
			down(semid, 0, 1);
			printf("Imprimiendo color del segundo club...\n");
			sleep(1);
			buffer[(2*i*4) + 4] = bandera_club[3*i];
			buffer[(2*i*4) + 5] = bandera_club[3*i+1];
			buffer[(2*i*4) + 6] = bandera_club[3*i+2];
			if(i != 2)
				buffer[(2*i*4) + 7] = '-';
			printf("COLOR IMPRESO: %c%c%c\n", bandera_club[3*i], bandera_club[3*i+1], bandera_club[3*i+2]);
			up(semid, 0, 1);
			usleep(1);
		}
		up(semid, 1, 1);
		return 0;
	}

	
	usleep(3); // Dormimos el proceso tres nanosegundos para asegurarnos que ambos clubes hagan downs
		   // del semaforo
	down(semid, 1, 2); // Down del semaforo, tomando dos recursos
	
	printf("\n--------------------------\n\nBANDERA FINAL:\n");
	printf("\t%s\n", buffer); // Imprimimos bandera

	up(semid, 1, 2);

	// Liberamos el buffer compartido y los semaforos
	shmdt((char *)buffer);
	shmctl(shmid, IPC_RMID, (struct shmid_ds *)NULL);
	semctl(semid, 0, IPC_RMID);
	semctl(semid, 1, IPC_RMID);

	return 0;
}

void down(int semid, int id, int recursos){
	struct sembuf sem_lock = {id, (-1*recursos)};
	if (semop(semid, &sem_lock, 1) == -1){
		perror("Problema con semop");
		exit(1);
	}
}

void up(int semid, int id, int recursos){
	struct sembuf sem_unlock = {id, recursos};
	if ((semop(semid, &sem_unlock, 1)) == -1){
		perror("Problema con semop");
		exit(1);
	}
}
