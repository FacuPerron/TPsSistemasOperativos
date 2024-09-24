#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void blanca();
void negra();
void alarma();

int huesped = 1;

int main(int argc, char *argv[]) {
    signal(SIGALRM, &alarma);
    signal(SIGUSR1, &blanca);
    signal(SIGUSR2, &negra);

    while(1){
        pause();
    }

    return 0;
}

    void blanca() {
        printf("Deseo tostadas de pan blanco.\n");
        printf("Tostadas de pan blanco.    (%d)\n", huesped);
        huesped++;

        alarm(1);
    }

    void negra() {
        printf("Deseo tostadas de pan negro.\n");
        printf("Tostadas de pan negro.    (%d)\n", huesped);
        huesped++;

        alarm(2);
        }

    void alarma(){

        printf("Tostadas listas.\n");

        printf("Tostadora libre, esperando pan.\n");
    }