#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>



int main(int argc, char *argv[]) {
	
	printf("Año 2023, 2C. Grupo n° 44. \nIntegrantes: Perron Facundo, perronfacundo2015@gmail.com \nManuel Calvo, mancalvo@frsf.utn.edu.ar \n");
	printf("Valentino Delarmelina, valentinodelarmelina@outlook.com \n");

    if(argc != 2)     // Verificamos que se haya enviado PID de la tostadora como argumento
        printf("Modo de uso: ./ejercicio4_huesped [PID_TOSTADORA]\n");
    else {
        for(int i = 1; i <= 30; i++) {
            if(i % 5 == 0) { // Pan negro, uno de cada cinco huespedes
                kill(atoi(argv[1]), SIGUSR2); // Enviamos señal SIGUSR2 al PID especificado
                printf("Pedido de tostada de Pan Negro. Huesped: %d\n", i);
                sleep(2);
            }
            else { // Pan blanco
                kill(atoi(argv[1]), SIGUSR1); // Enviamos señal SIGUSR2 al PID especificado
                printf("Pedido de tostada de Pan Blanco. Huesped: %d\n", i);
                sleep(1);
            }
        }

    }
    pid_t pid = atoi(argv[1]);
    kill(pid, SIGKILL); // Una vez pasaran los treinta huespedes, enviamos KILL a la tostadora.
    return 0;
}
