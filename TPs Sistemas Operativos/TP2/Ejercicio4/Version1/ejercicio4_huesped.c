#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <sys/syscall.h>


static int pidfd_send_signal(int pidfd, int sig, siginfo_t *info, unsigned int flags) {
    return syscall(SYS_pidfd_send_signal, pidfd, sig, info, flags);
}

void alarm_handler();

int main(int argc, char *argv[]) {
	signal(SIGALRM, alarm_handler);
	if(argc != 2)
		printf("Modo de uso: ./ejercicio4_huesped [PID_TOSTADORA]\n");
	else {
		for(int i = 1; i <= 30; i++) {
			if(i % 5 == 0) { // Pan negro
				siginfo_t inf;
				memset(&inf, 0, sizeof(inf));
				inf.si_code = SI_QUEUE;
				inf.si_signo = SIGUSR2;
				inf.si_pid = getpid();
				inf.si_int = i;
				char path[PATH_MAX];
				sprintf(path, "/proc/%s", argv[1]);
				int pidfd = open(path, O_RDONLY);
				if(pidfd == -1)
					return 1;

				if(pidfd_send_signal(pidfd, SIGUSR2, &inf, 0) == -1) {
					perror("pidf_send_signal");
					exit(1);
				}
				printf("Pedido de tostada de Pan Negro. Huesped: %d\n", i);
				pause();
			}
			else { // Pan blanco
				siginfo_t inf;
				memset(&inf, 0, sizeof(inf));
				inf.si_code = SI_QUEUE;
				inf.si_signo = SIGUSR1;
				inf.si_pid = getpid();
				inf.si_int = i;
				char path[PATH_MAX];
				sprintf(path, "/proc/%s", argv[1]);
				int pidfd = open(path, O_RDONLY);
				if(pidfd == -1)
					return 1;

				if(pidfd_send_signal(pidfd, SIGUSR1, &inf, 0) == -1) {
					perror("pidf_send_signal");
					exit(1);
				}
				printf("Pedido de tostada de Pan Blanco. Huesped: %d\n", i);
				pause();
			}
		}

	}
	pid_t pid = atoi(argv[1]);
	kill(pid, SIGKILL);
	return 0;
}

void alarm_handler() {}
