#include <bits/types/siginfo_t.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <sys/syscall.h>
#include <stdlib.h>

static int pidfd_send_signal(int pidfd, int sig, siginfo_t *info, unsigned int flags) {
    return syscall(SYS_pidfd_send_signal, pidfd, sig, info, flags);
}


void blanca(int sig, siginfo_t *inf, void *context);
void negra(int sig, siginfo_t *inf, void *context);

int main(int argc, char *argv[]) {

	struct sigaction actBlanca = {0};
        actBlanca.sa_sigaction = blanca;
	actBlanca.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &actBlanca, NULL);

	struct sigaction actNegra = {0};
        actNegra.sa_sigaction = negra;
	actNegra.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &actNegra, NULL);
	while(1) {
		pause();
	}
	
	return 0;
}

	void blanca(int sig, siginfo_t *inf, void *context) {
		printf("Deseo tostadas de pan blanco.\n");
		printf("Tostadas de pan blanco.	(%d)\n", inf->si_int);

		sleep(1);
		printf("Tostadas listas.\n");

		kill(inf->si_pid, SIGALRM);

		printf("Tostadora libre, esperando pan.\n");
	}

	void negra(int sig, siginfo_t *inf, void *context) {
	
		printf("Deseo tostadas de pan negro.\n");
		printf("Tostadas de pan negro.	(%d)\n", inf->si_int);

		sleep(2);
		printf("Tostadas listas.\n");

		kill(inf->si_pid, SIGALRM);

		printf("Tostadora libre, esperando pan.\n");
	}
	
