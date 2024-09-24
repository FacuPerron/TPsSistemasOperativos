#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <fcntl.h> 
#include <errno.h> 
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <string.h>


// Definimos las estructuras para mensajes
struct message_text {
    int qid;
    char buf[25];
};

struct message {
    long message_type;
    struct message_text message_text;
};

 
int main(int argc, char *argv[]) 
{ 
    char *dt_ptr; 
    time_t t_secs; 
    int ret; 
    struct message message;

    // Imprimimos nuestros nombres
    printf("Año 2023, 2C. Grupo n° 44.\n");
    printf("Integrantes: Perrón Facundo, perronfacundo2015@gmail.com\n");
    printf("Manuel Calvo, mancalvo@frsf.utn.edu.ar\n");
    printf("Valentino Delarmelina, valentinodelarmelina@outlook.com\n\n");	
    
    // Definimos la clave y la queue del servidor
    key_t clave = ftok("/tmp/datetime_queue", 'a');

    int qid;
    if((qid = msgget(clave, IPC_CREAT|0666)) == -1) {
	perror("Problema con msgget");
	exit(1);
    }
    
    while(1) {
    	// Recibimos mensajes en la cola:
        if(msgrcv(qid, &message, sizeof(struct message_text), 2, 0) == -1) {
	   perror("Problema con msgrcv");
	   exit(1);
        }
    	
    	// Imprimimos el contenido del buffer del mensaje, que contiene el PID del cliente
    	printf("%s", message.message_text.buf);
    
    	// Guardamos el qid del cliente
    	int client_qid = message.message_text.qid;
    
    	// Definimos los campos para la respuesta:
    	message.message_text.qid = qid;
    	message.message_type = 1;
    	t_secs = time(NULL);
    	dt_ptr = ctime(&t_secs);
    	sprintf(message.message_text.buf, "%s", dt_ptr);
    
    	// Continuado al PID, impimimos la fecha y hora actual
    	printf(" - %s", dt_ptr); 
    	
    	// Enviamos al cliente el mensaje con la fecha y hora
         if(msgsnd(client_qid, &message, sizeof(struct message_text), 0) == -1) {
	   perror("Problema con msgsnd");
	   exit(1);
        }   
    	// Seguimos en bucle... 
    }
    return 0; 
} 

