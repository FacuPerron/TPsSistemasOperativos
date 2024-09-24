#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <fcntl.h> 
#include <errno.h> 
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <signal.h>

void intHandler(int);
 
int main(int argc, char *argv[]) 
{ 
	
	// Imprimimos nuestros nombres
	printf("Año 2023, 2C. Grupo n° 44.\n");
	printf("Integrantes: Perrón Facundo, perronfacundo2015@gmail.com\n");
	printf("Manuel Calvo, mancalvo@frsf.utn.edu.ar\n");
	printf("Valentino Delarmelina, valentinodelarmelina@outlook.com\n\n");	

	signal(SIGINT, intHandler); // Definimos manejador de interrupción
	char *dt_ptr; 
	time_t t_secs; 
	int ret; 
	 
	// crea la FIFO  
	ret =  mkfifo("/tmp/datetime.fifo", 0666); 
 
	if(ret < 0) { 
		fprintf(stderr,"Error %d al crear FIFO\n", errno); 
		exit(1); 
	} 
 
	while(1) {
		char pid[10];
		int fd = open("/tmp/datetime.fifo", O_RDONLY); // Abrimos y bloqueamos la FIFO
		read(fd, pid, 10); // Al desbloquearse la FIFO, leemos el pid escrito por el cliente
		close(fd);
		char directory[30];
		sprintf(directory, "/tmp/%s.fifo", pid); // Guardamos directorio de la fifo cliente en "directory"
		int pid_file = open(directory, O_WRONLY); // Abrimos directory para comunicarle al cliente la fecha
		t_secs = time(NULL); 
		dt_ptr = ctime(&t_secs); 
		printf("%s - %s", pid, dt_ptr); // Imprimimos en pantalla el PID cliente y la fecha
		write(pid_file, dt_ptr, 25); // Pasamos la informacion al cliente
		close(pid_file); // Cerramos la FIFO
		// Seguimos en bucle... 
	}
	 
} 

// Implementamos funcionalidad en interrupción, para eliminar correctamente la FIFO servidor
void intHandler(int inp) { 
	int ret = unlink("/tmp/datetime.fifo"); 
	if(ret < 0) { 
		fprintf(stderr,"Error %d al suprimir FIFO\n", errno); 
	} 
	exit(1); 
}
