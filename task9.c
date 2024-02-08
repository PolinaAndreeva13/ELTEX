#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void my_handler(int nsig){ 

	printf("\nA signal was received under number %d and name %s\n", nsig, strsignal(nsig));
	
}

int main(void){ 
    
	for (int i = 1; i <= NSIG; i++) {
		
		signal(i, my_handler);
    
	}

    while(1);
    return 0;
}

