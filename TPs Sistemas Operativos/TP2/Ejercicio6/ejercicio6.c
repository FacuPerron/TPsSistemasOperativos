#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

int main() {

	printf("Año 2023, 2C. Grupo n° 44. \nIntegrantes: Perron Facundo, perronfacundo2015@gmail.com \nManuel Calvo, mancalvo@frsf.utn.edu.ar \n");
	printf("Valentino Delarmelina, valentinodelarmelina@outlook.com \n");

	struct utsname info;  // Definimos estructura de tipo _struct utsname_
	uname(&info);         // Llamamos a la syscall uname

  // Imprimimos los campos resultantes en la estructura
	printf("Tipo de Sistema: %s\n", info.sysname);
	printf("Nombre del Equipo: %s\n", info.nodename);
	printf("Version del Kernel: %s\n", info.release);
	printf("Version del S.O.: %s\n", info.version);
	printf("Arquitectura: %s\n", info.machine);
	return 0;
}
