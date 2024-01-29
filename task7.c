#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<sys/syscall.h>
#define PERMS 0777

int print_cat(char *argv){

	char buf[BUFSIZ];
	size_t size;
	int fd = open(argv, O_RDONLY, PERMS);

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

		return 1;

}

int enter_cat(char *argv) {
	
	char buf[BUFSIZ];
	size_t size;
	int fd = creat(argv, PERMS);

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

	return 1;

}

int main(int argc, char *argv[]){

	if (argc != 2) {
	
		perror("Command operation: <command> <file_name>\n");
		exit(1);

	}	

	/*if (argc == 3){
	 
	 	enter_cat(argv[2]);

	} else {*/
	
		print_cat(argv[1]);	

	
	//} 
	
}
