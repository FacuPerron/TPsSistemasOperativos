#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	printf("Año 2023, 2C. Grupo n° 44. \nIntegrantes: Perron Facundo, perronfacundo2015@gmail.com \nManuel Calvo, mancalvo@frsf.utn.edu.ar \n");
	printf("Valentino Delarmelina, valentinodelarmelina@outlook.com \n");

	pid_t pid = getpid(); // Guardamos nuestro PID
	printf("Id proceso que invoca: %d\n", pid); // Mostramos nuestro PID
	execv("./ejercicio3_factorial", argv); // Ejecutamos el programa "ejercicio3_factorial" pasandole nuestros argumentos
}

