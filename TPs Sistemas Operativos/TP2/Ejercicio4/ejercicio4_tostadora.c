#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// Definimos funciones a utilizar para recibir señales
void blanca(int sig, siginfo_t *inf, void *context);
void negra(int sig, siginfo_t *inf, void *context);

void tostadora_libre();

int huesped = 1;

int main(int argc, char *argv[]) {

  // Definimos estructuras para recepcion de señales
	struct sigaction actBlanca = {0};
  actBlanca.sa_sigaction = blanca;        // Función a ejecutar al recibir señal
	actBlanca.sa_flags = SA_SIGINFO;        // Asignamos la constante SA_SIGINFO a actBlanca.sa_flags,
                                          // para que se evalúe el campo de
                                          // sa_sigaction como la función a ejecutar.
	sigaction(SIGUSR1, &actBlanca, NULL);   // Ejecutamos la syscall que cambia la recepción de la señal SIGUSR1
                                          // por lo que especificamos en la estructura


  // Mismo caso que con actBlanca, pero ahora enviamos a función _negra_ y la señal _SIGUSR2_
	struct sigaction actNegra = {0};
  actNegra.sa_sigaction = negra;
	actNegra.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &actNegra, NULL);

  while(1){     // Dejamos el programa en ejecución, a la espera de las señales
    pause();
  }

  return 0;
}

// Si recibimos la señal SIGUSR1 ejecutamos:
void blanca(int sig, siginfo_t *inf, void *context) {     
  printf("Deseo tostadas de pan blanco.\n");
  printf("Tostadas de pan blanco.    (%d)\n", huesped);
  huesped++;  // Vamos llevando recuento de huespedes
  
  tostadora_libre();
}

// Si recibimos la señal SIGUSR2 ejecutamos:
void negra(int sig, siginfo_t *inf, void *context) {
  printf("Deseo tostadas de pan negro.\n");
  printf("Tostadas de pan negro.    (%d)\n", huesped);
  huesped++;  // Vamos llevando recuento de huespedes

  tostadora_libre();
}

void tostadora_libre(){

  printf("Tostadas listas.\n");

  printf("Tostadora libre, esperando pan.\n");
}
