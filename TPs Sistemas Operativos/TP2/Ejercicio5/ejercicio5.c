#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int pasada = 1;  // Variable global de control
void intHandler(int);

int main(int argc, char *argv[]) {

	printf("Año 2023, 2C. Grupo n° 44. \nIntegrantes: Perron Facundo, perronfacundo2015@gmail.com \nManuel Calvo, mancalvo@frsf.utn.edu.ar \n");
	printf("Valentino Delarmelina, valentinodelarmelina@outlook.com \n");

	signal(SIGINT, intHandler);  // Dirigimos las señales SIGINT a la función intHandler

	printf("Iteracion INICIADA. Presionar Ctrl-C NO tiene efecto...\n");
	for(int i = 0; i <= 100000; i++) {
		if(i % 1000 == 0) 
			printf("Iteracion %d\n", i);
	}
	printf("Computation is done\n");
	pasada++;                         // Luego de las primeras cien mil iteraciones, incrementamos la variable de control
	printf("\n");
	
	printf("Reinicio de la Iteracion. Precionar Ctrl-C AHORA tiene efecto...\n");
	for(int i = 0; i <= 100000; i++) {
		if(i % 1000 == 0) 
			printf("Iteracion %d\n", i);
	}
	printf("Computation is done\n");
	return 0;
}

void intHandler(int inp) {
  // Si se recibe la interrupción y la variable de control no fue incrementada, se la ignora.
  // Si se recibe la interrupción y la variable de control fue incrementada, se sale del programa.
	if(pasada > 1)
		exit(0);
}
