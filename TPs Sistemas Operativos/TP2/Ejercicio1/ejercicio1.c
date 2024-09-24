#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

printf("Año 2023, 2C. Grupo n° 44. \nIntegrantes: Perron Facundo, perronfacundo2015@gmail.com \nManuel Calvo, mancalvo@frsf.utn.edu.ar \n");
printf("Valentino Delarmelina, valentinodelarmelina@outlook.com \n");

int opt, z, i;
FILE *arch;
	if (argc==1){    // Caso donde no se insertan argumentos.
		printf("Uso: %s [-cl] [-s nombre_archivo]\n", argv[0]);
	} else if (argc > 1){ // Caso donde se inserta al menos un argumento
		 while ((opt = getopt(argc, argv, "cls:")) != -1) { // Recorre los argumentos, tomandolos uno a uno y asignandoselos a opt
			switch(opt){
			case 'c': 
				printf("Cantidad de argumentos: %i\n",argc);  // Si 'c' es argumento, mostramos la cantidad de argumentos
				break;
			case 'l':
				for(i=0;i<argc;i++){
					printf("Argumento %i: %s\n",i,argv[i]);    // Si 's' es argumento, listamos los argumentos
				}
				break;
			case 's':
				arch=fopen(argv[argc-1],"w");              // Si 'l' es argumento, creamos/abrimos el archivo de argumento y le cargamos
                                                     // los argumentos
				if (arch==NULL)
					exit(1);
				for(z=0;z<argc;z++){
					fputs(argv[z],arch);
				}
				break;
			}
		}
	}
	return 0;
}
