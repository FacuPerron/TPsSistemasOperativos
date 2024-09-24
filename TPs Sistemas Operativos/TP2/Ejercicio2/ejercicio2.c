#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){

	printf("Año 2023, 2C. Grupo n° 44. \nIntegrantes: Perron Facundo, perronfacundo2015@gmail.com \nManuel Calvo, mancalvo@frsf.utn.edu.ar \n");
	printf("Valentino Delarmelina, valentinodelarmelina@outlook.com \n");
	
	int padre, hijo1, division1, valor1, valor, division2, hijo2, valor2, division3, hijo3, valor3, division4, hijo4, valor4;
	
	if(argc != 2) { // Si no se insertan la cantidad de argumentos adecuados, salimos
		printf("Uso: %s [NUMERO]\n", argv[0]);
		return 1;
	}

	char *aux = argv[1];
	valor = atoi(aux);    // Realizamos casteo del argumento
		
	padre = getpid();     // Guardamos PID del padre
	
	printf("NODO R - VALOR = %d\n", valor);
	printf("ID proceso raiz: %d\n\n", padre);
	
	division1 = fork(); // Creamos hijo izquierdo del padre
                      
	if(division1 == 0){ // Código que ejecuta el hijo izquierdo
		valor1 = valor + 100;
		hijo1 = getpid();
		printf("NODO 1 - VALOR = %d\n", valor1);
		printf("ID NODO 1: %d - ID padre NODO 1(NODO R): %d\n\n", hijo1, getppid());

		division2 = fork();  // Se crea hijo izquierdo del hijo izquierdo
		if(division2 == 0){
			valor2 = valor1 * 2;
			hijo2 = getpid();
			printf("NODO 1.1 - VALOR = %d\n", valor2);
			printf("ID NODO 1.1: %d - ID padre NODO 1.1(NODO 1): %d\n\n", hijo2, getppid());
		}

    if(getpid() == hijo1) {  // Código que ejecuta sólo el hijo izquierdo
	  	division3 = fork();    // Se crea hijo derecho del hijo izquierdo
	  	if(division3 == 0){
	  		valor3 = valor1 / 2;
	  		hijo3 = getpid();
	  		printf("NODO 1.2 - VALOR = %d\n", valor3);
	  		printf("ID NODO 1.2: %d - ID padre NODO 1.2(NODO 1): %d\n\n", hijo3, getppid());
	  	}
    }
	}

  if(getpid() == padre) {  // Código que ejecuta sólo el padre
	  division4 = fork();    // Se crea hijo derecho del padre
  	if(division4 == 0){
  		valor4 = valor - 100;
  		hijo4 = getpid();
  		printf("NODO 2 - VALOR = %d\n", valor4);
  		printf("ID NODO 2: %d - ID padre NODO 2(NODO R): %d\n\n", hijo4, getppid());
  	}
  }
	return 0;
}
