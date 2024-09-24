#include <stdio.h>
#include <stdlib.h>	
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
	int top = atoi(argv[1]);  // Tomamos el argumento y lo marcamos como nuestro tope
	pid_t pid = getpid();     // Guardamos nuestro PID
	if(argc == 2){            // Verificamos que la cantidad de argumentos sea correcta
		if(top < 1 || top > 10) {  // Si el número está fuera de rango, lo anunciamos
			printf("Numero fuera de rango: %s\n",argv[1]);
		} else {  // Calculamos factorial
			long fac = 1;
			for(int i = 1; i <= top; i++) {
			fac *= i;
			}
			printf("Factorial de %d = %ld\n", top, fac);              // Printeamos el factorial
		}
		printf("Id de Prg-Factorial: %d\n", pid);                  // Printeamos nuestro PID
	} else{
		printf("Error. Usar ./Nombre_pgr_invoca [número]\n");     // Mostramos error si no se cumple con los argumentos
	}
	
	return 0;
}
