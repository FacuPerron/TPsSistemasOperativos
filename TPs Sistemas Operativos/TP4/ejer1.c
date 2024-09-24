#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <linux/ext2_fs.h>
int main(){
	
	int fd;
	    struct ext2_super_block superblock;

    // Abre el dispositivo del sistema de archivos (por ejemplo, /dev/fd0 para un diskette)
    fd = open("/dev/fd0", O_RDONLY);
	if (fd == -1) {
        perror("Error al abrir el dispositivo");
        return 1;
    }

 // Lee el superblock
   pread(fd, &superblock, sizeof(superblock), 1024); 
    
	    
if (superblock.s_magic == EXT2_SUPER_MAGIC) {
	printf("----------------------INFORMACION DEL SB-----------------\n");
	printf("Sistema de archivos tipo: EXT2\n");
	printf("Nombre del Volumen: %s\n", superblock.s_volume_name);
	printf("Cantidad de i-nodos: %d\n", superblock.s_inodes_count);
	printf("Cantidad de i-nodos libres:%d\n", superblock.s_free_inodes_count);
	printf("Primer i-nodo no reservado: %d\n", superblock.s_first_ino);
	printf("Tamaño estructura de un i-nodo: %d\n", superblock.s_inode_size);
	int  block_size = 1024 << superblock.s_log_block_size;
	printf("Tamaño de bloque: %d\n",  block_size);
	printf("Primer bloque de datos: %d\n", superblock.s_first_data_block);
	printf("Cantidad de bloques: %d\n", superblock.s_blocks_count);
	printf("Cantidad de bloques libres: %d\n", superblock.s_free_blocks_count);
	printf("Espacio total en disco: %d\n", superblock.s_blocks_count*block_size);
	printf("----------------------------------------------------------");
	
	 } else {
        printf("No es un diskette con filesystem de tipo ext2\n");
    }

	

    


    close(fd);

	
	
	
	
	return 0;
}
