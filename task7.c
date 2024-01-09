#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/syscall.h>
#define PERMS 0777

int main(int argc, char *argv[]){

	if (argc != 2) {
	
		perror("Command operation: <command> <file_name>\n");
		exit(1);

	}

	char buf[BUFSIZ];
	size_t size;	

	/*if (argc == 3){
		
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

	} else {*/
	
		int fd = open(argv[1], O_RDONLY, PERMS);

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
	
//	} 
	
}
