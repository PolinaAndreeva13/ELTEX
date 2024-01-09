#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/syscall.h>
#define PERMS 0777

int main(int argc, char *argv[]){

	if (argc != 3) {
	
		perror("Command operation: <command> <mode> <file_name>\nmode: 1 - read; 2 - write\n");
		exit(1);

	}

	char buf[BUFSIZ];
	size_t size;
	
	if (strcmp(argv[1], "1") == 0){

		int fd = open(argv[2], O_RDONLY, PERMS);

		if (fd == -1) {

			perror("Error opened");
			exit(1);

		}
	
		while ((size = read(fd, buf, BUFSIZ)) > 0){
	
			if (write(1, &buf, size) != size){
		
				perror("FATAL");
				exit(1);
		
			}	
	
		}

		close(fd);

	}

	if (strcmp(argv[1], "2") == 0) {
		
		int fd = creat(argv[2], PERMS);

		if (fd == -1) {
		
			perror("Error opened");
			exit(1);

		}

		while((size = read(0, buf, BUFSIZ)) > 0) {
	
			if (write(fd, &buf, size) != size){
			
				perror("FATAL");
				exit(1);

			}

		}

		close(fd);

	}

}

