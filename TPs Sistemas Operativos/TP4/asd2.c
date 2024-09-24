#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
#include <linux/ext2_fs.h>

void print_file_info(struct ext2_inode inode, char *name) {
    struct tm *time_info;
    char time_str[20];

    printf("Number of inode: %u\n", inode.i_mode & 0xFFFFFFF);
    printf("Access mode: %#o\n", inode.i_mode & 0xFFF);
    printf("Number of links: %u\n", inode.i_links_count);
    printf("User: %u\n", inode.i_uid);
    printf("Group: %u\n", inode.i_gid);
    printf("Filesize: %u bytes\n", inode.i_size);

    // Convert __le32 to time_t
    time_t atime = inode.i_atime;
    time_info = localtime(&atime);

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    printf("Date: %s\n", time_str);

    printf("Name of file: %s\n", name);
    printf("---------------------\n");
}

int main() {
    // Open the floppy disk device
    int fd = open("/dev/fd0", O_RDONLY);
    if (fd == -1) {
        perror("Error opening floppy disk");
        return 1;
    }

    // Read the superblock
    struct ext2_super_block superblock;
    ssize_t bytesRead = read(fd, &superblock, sizeof(struct ext2_super_block));
    if (bytesRead == -1) {
        perror("Error reading superblock");
        close(fd);
        return 1;
    }

    printf("Read superblock successfully\n");

    // Read the root inode
    struct ext2_inode root_inode;
    off_t rootInodeOffset = superblock.s_first_data_block * EXT2_BLOCK_SIZE(&superblock);
    lseek(fd, rootInodeOffset, SEEK_SET);
    bytesRead = read(fd, &root_inode, sizeof(struct ext2_inode));
    if (bytesRead == -1) {
        perror("Error reading root inode");
        close(fd);
        return 1;
    }

    printf("Read root inode successfully\n");

// Read the root directory entries
struct ext2_dir_entry dir_entry;
int i;
int offset = 0;

for (i = 0; i < EXT2_NDIR_BLOCKS; ++i) {
    off_t block_offset = root_inode.i_block[i] * EXT2_BLOCK_SIZE(&superblock);

    if (block_offset > 0) {
        lseek(fd, block_offset, SEEK_SET);
        read(fd, &dir_entry, sizeof(struct ext2_dir_entry));

        // Continue reading and printing directory entries until the end
        while (dir_entry.inode != 0 && offset < root_inode.i_size) {
            // Print file information
            print_file_info(root_inode, dir_entry.name);

            // Move to the next entry
            offset += dir_entry.rec_len;
            off_t dir_entry_offset = block_offset + offset;
            lseek(fd, dir_entry_offset, SEEK_SET);
            read(fd, &dir_entry, sizeof(struct ext2_dir_entry));
        }

        break;  // Stop after reading the first non-empty block
    }
}

// Close the floppy disk device
close(fd);

return 0;
}