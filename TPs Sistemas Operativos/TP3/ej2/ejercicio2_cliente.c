#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <fcntl.h> 
#include <errno.h> 
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h> 
 
int main(int argc, char *argv[]) 
{ 
 
	int ret; 
	int pid = getpid();
	char directory[30];
	sprintf(directory, "/tmp/%d.fifo", pid);
	// crea la FIFO  
	ret =  mkfifo(directory, 0666); 
 
	if(ret < 0) { 
		fprintf(stderr,"Error %d al crear FIFO\n", errno); 
		exit(1); 
	} 
	 

	// Abrimos la FIFO del servidor en modo escritura
	int fd = open("/tmp/datetime.fifo", O_WRONLY);
	char pid_s[10];
	sprintf(pid_s, "%d", pid);
	write(fd, pid_s, 10); // Escribimos sobre la FIFO servidor nuestro PID
	close(fd); // Cerramos la FIFO

	int my_file = open(directory, O_RDONLY); // Abrimos la FIFO cliente
	char buffer[25];
	read(my_file, buffer, 25); // Leemos la fecha depositada por el servidor
	printf("%s", buffer); 

	close(my_file);
	 
	// Eliminamos la FIFO
	ret = unlink(directory); 
	if(ret < 0) { 
	fprintf(stderr,"Error %d al suprimir FIFO\n", errno); 
	exit(1); 
	} 
} 
