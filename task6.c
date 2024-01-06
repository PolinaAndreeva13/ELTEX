#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student {

        char Surname[100];
        int RecordBookNum;
        char Faculty[100];
        char Group[100];

};

int students(const char *path){

        int count_student = 0;
        FILE *pfile = fopen(path, "r");

        if (!pfile){

                perror("\nError opened");
                exit(1);
        }

        int ch = 0;

        while ((ch = fgetc(pfile)) != EOF) {
		
		if (ch == '\n') count_student++;

        }

        fclose(pfile);
        return count_student;

}

void save(struct student *save_student, int new_count, int flag, const char *path){

	FILE *pfile = fopen(path, flag == 0 ? "a" : "w");
    
	if (!pfile) {
	
		perror("\nError opened");
		exit(1);
	
	}

	if (flag == 0){
       		
		fprintf(pfile, "%s %d %s %s\n", save_student[new_count].Surname, save_student[new_count].RecordBookNum, save_student[new_count].Faculty, save_student[new_count].Group);
	
	} else {
	
		int counter_help = 0;

		while (counter_help < new_count){
		
			fprintf(pfile, "%s %d %s %s\n", save_student[counter_help].Surname, save_student[counter_help].RecordBookNum, save_student[counter_help].Faculty, save_student[counter_help].Group);

			counter_help++;

		}
	
	}


       	fclose(pfile);

}


struct student *load(int count_student, const char *path){

        struct student *all_students = NULL;
        FILE *pfile = fopen(path, "r");

        if (!pfile){

                perror("\nError opened.\n");
                exit(1);
        }
        if (count_student > 0){

                all_students = (struct student*)realloc(all_students, count_student * sizeof(struct student));
                int counter_help = 0;

                while (counter_help < count_student){
        
                        fscanf(pfile, "%99s%d%99s%99s", all_students[counter_help].Surname, &all_students[counter_help].RecordBookNum, all_students[counter_help].Faculty, all_students[counter_help].Group);
        
                        counter_help++;
    
                }                
       
        }

	fclose(pfile);
	return all_students;

}


void add_student(int count_student, struct student *all_students, const char *path){

        struct student *new_student = (struct student*)realloc(all_students, (count_student + 1) * sizeof(struct student));
         
        new_student = new_student + count_student;

        printf("Please enter the following information:\nSurname: ");
        scanf("%99s", new_student->Surname);
        
	printf("Record Book Number: ");
	int num = 0;
	int flag = scanf("%d", &num);
	if (flag == 0) {
	
		printf("You can only enter numbers.\nDefault value is 0.\n");
		new_student->RecordBookNum = 0;
		while (getchar() != '\n');

	} else {

		new_student->RecordBookNum = num;
	
	}	

        printf("Faculty: ");
        scanf("%99s", new_student->Faculty);
        printf("Group: ");
        scanf("%99s", new_student->Group);

        new_student = new_student - count_student;

        save(new_student, count_student, 0, path);

        printf("\nThe student has been successfully added!\n");

}

void print_table(const char *path){

        FILE *pfile = fopen(path, "r");

        if (!pfile) {
                perror("\nError opened");
                return;
        }

        printf("|%-17s | %-15s | %-15s | %-10s |\n", "Surname student", "Record book number", "Faculty", "Group");
        printf("|--------------------------------------------------------------------------|\n");

        struct student student_view;

        while (fscanf(pfile, "%99s%d%99s%99s", student_view.Surname, &student_view.RecordBookNum, student_view.Faculty, student_view.Group) == 4) {
        
                printf("| %-20s | %-15d | %-15s | %-10s |\n", student_view.Surname, student_view.RecordBookNum, student_view.Faculty, student_view.Group);
    
        }

        fclose(pfile);

}

void delete_student(struct student *all_students, int count_student, const char* path){

        printf("\nEnter the last name of the student you want to remove from the table: ");
        char surname[100];
        scanf("%99s", surname);

        int index_del = -1;

        for (int i = 0; i < count_student; i++){

                if (strcmp(all_students[i].Surname, surname) == 0){
			
			index_del = i;
			break;
                }

        }

	if (index_del != -1){
        	
		for (int i = index_del; i < count_student; i++){
			
			all_students[i] = all_students[i + 1];

        	}
	
		struct student *new_students = (struct student*)realloc(all_students, (count_student - 1) * sizeof(struct stuent*));

		for (int i = 0; i < count_student - 1; i++){
	
			new_students[i] = all_students[i];

		}

        /*for(int i = 0; i < count_student - 1; i++){

                printf("Surnmae:%s\nRecord Book Number:%d\nFaculty:%s\nGroup:%s\n", new_students[i].Surname, new_students[i].RecordBookNum, new_students[i].Faculty, new_students[i].Group);


        }*/
        
		save(new_students, count_student - 1, 1, path);

       		printf("\nThe deletion was completed successfully!\n");
	
	} else { 
	
		printf("\nSuch a person does not exist.\n");
	
	}

} 

void edit(struct student *all_students, int count_students, const char *path){

	print_table(path);
	printf("\nEnter the last name of the student whose information you want to edit: ");
	
	char surname[100];
	scanf("%99s", surname);
	
	int index_edit = -1;

	for (int i = 0; i < count_students; i++){
	
		if (strcmp(all_students[i].Surname, surname) == 0) {
		
			index_edit = i;
			break;
		
		}
	
	}
	
	if (index_edit != -1){
	
		printf("\nPlease indicate the field you want to change.\n(1)Surname\n(2)Record book number\n(3)Faculty\n(4)Group\nYour choise: ");
	
		int cmd = 0, test = 1, flag = 0;;
		flag = scanf("%d", &cmd);
		
		if (flag == 1){
	
			printf("\nEnter a new value for the selected filed: ");

			switch (cmd){

				case 1:

					scanf("%99s", all_students[index_edit].Surname);
					break;

				case 2:
				
					int num = 0;
					test = scanf("%d", &num);

					if (test == 0) {
			
						printf("\nYou can only enter whole numbers.\n");
						while (getchar() != '\n');

				
					} else {
					
						all_students[index_edit].RecordBookNum = num;

					}
					
					break;

				case 3:
			
					scanf("%99s", all_students[index_edit].Faculty);
					break;

				case 4:
			
					scanf("%99s", all_students[index_edit].Group);
					break;

				default:

					printf("\nNo such option.\n");
	
			}
		
			if (test == 1) save(all_students, count_students, 1, path);

		} else { 
		
			printf("\nIncorrect data.\n");
			while (getchar() != '\n');

		}
	
	} else {
	
		printf("\nSuch a person does not exist.\n");
	
	}

}

void sort(struct student *all_students, int count_student, const char *path){
	
	printf("\nSelect a field to sort.\n(1)Surname\n(2)Record book number\n(3)Faculty\n(4)Group\nYour choise: ");

	int cmd = 0;
	int flag = scanf("%d", &cmd);

	if (flag == 1){
	
		switch(cmd){

			case 1:

		  		for (int i = 0; i < count_student - 1; i++) {

                			for (int j = 0; j < count_student - i - 1; j++) {

                                		if (strcmp(all_students[j].Surname, all_students[j + 1].Surname) > 0) {

                                        		struct student temp = all_students[j];
                                        		all_students[j] = all_students[j + 1];
                                        		all_students[j + 1] = temp;

                                		}
                        		}
				}

				break;

			case 2:		
			
				for (int i = 0; i < count_student - 1; i++) {

                                	for (int j = 0; j < count_student - i - 1; j++) {

                                        	if (all_students[j].RecordBookNum > all_students[j + 1].RecordBookNum) {

                                        		struct student temp = all_students[j];
                                        		all_students[j] = all_students[j + 1];
                                        		all_students[j + 1] = temp;

                                        	}
                                	}
                        	}

				break;

			case 3:

				for (int i = 0; i < count_student - 1; i++) {

                                	for (int j = 0; j < count_student - i - 1; j++) {

                                        	if (strcmp(all_students[j].Faculty, all_students[j + 1].Faculty) > 0) {

                                        		struct student temp = all_students[j];
                                        		all_students[j] = all_students[j + 1];
                                        		all_students[j + 1] = temp;

                                        	}
                                	}
                        	}

				break;

			case 4:

				for (int i = 0; i < count_student - 1; i++) {

                                	for (int j = 0; j < count_student - i - 1; j++) {

                                        	if (strcmp(all_students[j].Group, all_students[j + 1].Group) > 0) {

                                                	struct student temp = all_students[j];
                                                	all_students[j] = all_students[j + 1];
                                                	all_students[j + 1] = temp;

                                        	}
                                	}
                        	}

				break;

			default:

				printf("There is no such option!");
				break;

		}
	
		save(all_students, count_student, 1, path);
		printf("\nSorting completed successfully!\n");

	} else {

		while (getchar() != '\n');

	}
	
}

int min(int a, int b, int c) {
	
	int min = a;
    
	if (b < min) {
        
		min = b;
    
	}
    
	if (c < min) {
        
		min = c;
    
	}
    
	return min;

}

int distance(char *str1, char *str2) {
    
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int dp[len1 + 1][len2 + 1];
	
	for (int i = 0; i <= len1; i++) {
        
		for (int j = 0; j <= len2; j++) {
            
			if (i == 0) {
                
				dp[i][j] = j;
            
			} else if (j == 0) {
                
				dp[i][j] = i;
            
			} else {
                
				dp[i][j] = min(dp[i - 1][j - 1] + (str1[i - 1] == str2[j - 1] ? 0 : 1),
                                dp[i][j - 1] + 1,
                                dp[i - 1][j] + 1);
            }
        }
    }

    return dp[len1][len2];
}

void search(struct student *all_students, int count_student, const char *path){

	printf("\nSelect search field.\n(1)Surname\n(2)Record book number\n(3)Faculty\n(4)Group\nYour choise: ");

	int cmd = 0, flag = 0;
	int cmd_flag = scanf("%d", &cmd);

	if (cmd_flag == 1) {
		
		switch(cmd){

			case 1:
			
				char surname[100];
				printf("\nEnter surname: ");
				scanf("%99s", surname);
				
				for (int i = 0; i < count_student; i++){
					
					if (distance(all_students[i].Surname, surname) < 3) {

						printf("Surnmae: %s\nRecord Book Number: %d\nFaculty: %s\nGroup: %s\n", all_students[i].Surname, all_students[i].RecordBookNum, all_students[i].Faculty, all_students[i].Group);
						printf("\n");
						flag = 1;

					}

				}
				break;

			case 2:

				int number;
				printf("\nEnter record book number: ");
				int test = scanf("%d", &number);

				if (test == 1) {
					
					for (int i = 0; i < count_student; i++){
				
						if (all_students[i].RecordBookNum == number){
				
                                        		printf("Surnmae: %s\nRecord Book Number: %d\nFaculty: %s\nGroup: %s\n", all_students[i].Surname, all_students[i].RecordBookNum, all_students[i].Faculty, all_students[i].Group);
							flag = 1;
							break;

                                		}

                        		}
				
				} else {

					while (getchar() != '\n');

				}
				break;

			case 3:

				char faculty[100];
                        	printf("\nEnter faculty: ");
                        	scanf("%99s", faculty);

                        	for (int i = 0; i < count_student; i++){

                                	if (distance(all_students[i].Faculty, faculty) < 3) {

                                        	printf("Surnmae: %s\nRecord Book Number: %d\nFaculty: %s\nGroup: %s\n", all_students[i].Surname, all_students[i].RecordBookNum, all_students[i].Faculty, all_students[i].Group);
    						printf("\n");
						flag = 1;

                                	}

                        	}
				break;

			case 4:

				char group[100];
                        	printf("\nEnter group: ");
                        	scanf("%99s", group);

                        	for (int i = 0; i < count_student; i++){

                                	if (distance(all_students[i].Group, group) < 3) {
                                        
						printf("Surnmae: %s\nRecord Book Number: %d\nFaculty: %s\nGroup: %s\n", all_students[i].Surname, all_students[i].RecordBookNum, all_students[i].Faculty, all_students[i].Group);
                                        	printf("\n");
						flag = 1;

                                	}

                        	}
				break;
		
			default:
			
				printf("There is no such option!");
				break;

		}
		
		if (flag == 0) {

			printf("\nNo such data.\n");

		}


	} else { 
	
		while (getchar() != '\n');
	
	}

}

void choise(const char *path){


        printf("Please select an action.\n(1)Writing to a table;\n(2)View table;\n(3)Sort the table in ascending order by a given field;\n(4)Search for an element in the table;\n(5)Delete entry;\n(6)Edit entry;\n(7)Exit.\n");

        int cmd = 0;
        printf("\nEnter your choise: ");
        int flag = scanf("%d", &cmd);
        

	while (cmd != 7 && flag != 0){

                switch (cmd){

                        case 1:{

                                        int count_student = students(path);
                      		        struct student *all_students = load(count_student, path);
                                        add_student(count_student, all_students, path);
                                        free(all_students);
                                        break;
				       
			       }
                        case 2:{

                                       	print_table(path);
                                       	break;
				       
				}
			case 3:{

					int count_student = students(path);
					struct student *all_students = load(count_student, path);
					sort(all_students, count_student, path);
					free(all_students);
					break;
				
				}
			case 4:{
			       
					int count_student = students(path);
					struct student *all_students = load(count_student, path);
					search(all_students, count_student, path);
					free(all_students);
					break;

			       }
			case 5:{
                                       
                                       	int count_student = students(path);
                                       	struct student *all_students = load(count_student, path);
                                       	delete_student(all_students, count_student, path);
				       	free(all_students);
                                       	break;


			       }
			case 6:{
			       
				       	int count_student = students(path);
				       	struct student *all_students = load(count_student, path);
				       	edit(all_students, count_student, path);
				       	free(all_students);
				       	break;
			       
				}
			default: {
					 printf("\nThere is no such option!\n"); 
					 break;
				 }
                	
		}
			printf("\nPlease select an action:\n(1)Writing to a table;\n(2)View table;\n(3)Sort the table in ascending order by a given field;\n(4)Search for an element in the table;\n(5)Delete entry;\n(6)Edit entry;\n(7)Exit.\n");
                	printf("\nEnter your choise: ");
                	flag = scanf("%d", &cmd);
	
	}

}

int main(){

        const char *path = "DB.txt";
        FILE *pfile = fopen(path, "a+");
        fclose(pfile);

        choise(path);

        return 0;

}
