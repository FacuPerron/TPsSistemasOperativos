#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <time.h> 
#include <fcntl.h> 
#include <errno.h> 
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/ipc.h>
#include <sys/msg.h>
 
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
    
    pid_t pid = getpid(); // Obtenemos PID del proceso
    
    // Definimos queue del cliente
    int myqid;
    if((myqid = msgget(IPC_PRIVATE, 0666)) == -1) {
	perror("Problema con msgget");
	exit(1);
    }
   
    // Obtenemos qid del servidor
    key_t clave = ftok("/tmp/datetime_queue", 'a');
    int server_qid;
    if((server_qid = msgget(clave, 0)) == -1) {
	perror("Problema con msgget");
	exit(1);
    }
    
    // Declaramos estructuras de mensaje para recepción y emisión de mensaje 
    struct message solicitud;
    struct message respuesta;
    
    // Preparamos mensaje para realizar solicitud al servidor
    solicitud.message_type = 2;
    solicitud.message_text.qid = myqid;
    sprintf(solicitud.message_text.buf, "%d", pid); // Almacenamos el pid como mensaje
    
    // Enviamos el mensaje y revisamos que se haga correctamente
    if((msgsnd(server_qid, &solicitud, sizeof(struct message_text), 0)) == -1) {
	perror("Problema con msgsnd");
	exit(1);
    }   
    
    // Recibimos respuesta del servidor y revisamos que se haga correctamente
    if(msgrcv(myqid, &respuesta, sizeof(struct message_text), 1, 0) == -1) {
	perror("Problema con msgrcv");
	exit(1);
    }
    
    // Imprimimos en pantalla respuesta del servidor
    printf("%s\n", respuesta.message_text.buf);
    
    // Eliminamos la queue del proceso y verificamos que se haga correctamente
    if(msgctl (myqid, IPC_RMID, NULL) == -1) {
	perror("Problema con msgctl");
	exit(1);
    }
    
    return 0;
} 
