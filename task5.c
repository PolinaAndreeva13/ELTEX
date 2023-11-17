#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *read_file() {
        FILE* pfile;
        pfile = fopen("/etc/passwd", "rb");
        long count_sym = 0;
        
        if (!pfile) {
                perror("Error opened");
        	exit(EXIT_FAILURE); 
	}
        else {
                fseek(pfile, 0, SEEK_END);
                count_sym = ftell(pfile);
                fseek(pfile, 0, SEEK_SET);
        }
	
        char *passwd = (char*)malloc(count_sym + 1);
        fread(passwd, 1, count_sym, pfile);
        //printf("%s", passwd);
	passwd[count_sym] = '\0';
        fclose(pfile);

        return passwd;
}

int check(char *login_check, char *login){
	char *container = (char*)malloc(strlen(login_check + 1));
	container[0] = '\0';
	for (int i = 0; i < strlen(login_check); i++){
		if (login_check[i] != ':'){
			strncat(container,&login_check[i],1);
		}
		else {
			break;
		}
	}
	//printf("%s ", login);
	//printf("%s\n", container);
	if (strcmp(login,container) == 0){
		free(container);
		return 1;
	}
	else {
		free(container);
		return 0;
	}

}

char *check_login(char *passwd, char *login) {
        char *login_check = (char*)malloc(strlen(passwd) + 1);
        char *container = (char*)malloc(strlen(passwd) + 1);
	login_check[0] = '\0';
	container[0] = '\0';

        for (int i = 0; i < strlen(passwd); i++){
                if (passwd[i] != '\n'){
                        strncat(login_check,&passwd[i],1);
                }
                else{
                        login_check[i]='\0';
                        int flag = check(login_check, login);
                        if (flag == 1){
                                //printf("%d",flag);
                                break;
                        }
                        else{
                                login_check[0]='\0';
                        }
                }
        }

        //printf("%s", login_check);
        int count_colon = 0;
        for (int i = 0; i < strlen(login_check); i++){
                if (login_check[i] == ':'){
                        count_colon++;
                        //printf("%d", count_colon);
                }
                if (count_colon == 4){
                        i++;
                        //printf("%d", count_colon);
                        while (login_check[i] != ':'){
                                strncat(container, &login_check[i], 1);
                                i++;
                        }
                        container[i] = '\0';
                        free(login_check);
			break;
                }
        }
	return container;	
}

char *output_username(char *passwd, char *login){
	char *container = check_login(passwd, login);
	char *username = (char*)malloc(strlen(container));
	username[0]='\0';
	int j = 0, flag = 0;

	for (int i = 0; i < strlen(container); i++){
		if (container[i] != ',') {
			j++;
		}
		else {
			flag = 1;
			break;
		}
	}

	if (flag == 0) {
		//printf("Your username: %s", container);
		return container;
	}
	else{
		//printf("%d\n",j);
		for (int i = 0; i < j; i++){
			strncat(username, &container[i], 1);
		}
		//printf("Your username: %s", username);
		return username;
	}
}

int main() {
        char login[20];
        printf("Please, input login: ");
        scanf("%19s", login);
        
	char *passwd = read_file();
        char *answer = output_username(passwd, login);
        free(passwd);
	
	if (strlen(answer) != 0) {
		printf("Your username: %s", answer);
		free(answer);
	}
	else { 
		printf ("This login does not exist or does not have a username");
		free(answer);
	}

	return 0;
}
