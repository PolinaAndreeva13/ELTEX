#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int del_shm(){

        char pathname[] = "sys1.c";
        key_t key;
        int shmid;

        if((key = ftok(pathname,0)) < 0){
        
                printf("Can\'t generate key\n");
                exit(-1);
    
        }

        if((shmid = shmget(key, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0) {
        
                if(errno != EEXIST){
            
                        printf("Can\'t create shared memory\n");
                        exit(-1);

                } else {

                        if((shmid = shmget(key, 3*sizeof(int), 0)) < 0){
                
                        printf("Can\'t find shared memory\n");
                        exit(-1);
            
                        }

                }
        }

        int err;
        if ((err = shmctl(shmid, IPC_RMID, NULL)) < 0){

                printf("FATAL");
                exit(-1);

        }

	return 1;

}

int main(){

	del_shm();	

}

