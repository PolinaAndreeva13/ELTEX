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

        if(!pfile){

                perror("Error opened");
                exit(1);
        }

        int ch = 0;

        while((ch = fgetc(pfile)) != EOF) {
		
		if (ch == '\n') count_student++;

        }

        fclose(pfile);
        return count_student;

}

void save(struct student *save_student, int new_count, int flag, const char *path){

	FILE *pfile = fopen(path, flag == 0 ? "a" : "w");
    
	if(!pfile) {
	
		perror("Error opened");
		exit(1);
	
	}

	if(flag == 0){
       		
		fprintf(pfile, "%s %d %s %s\n", save_student[new_count].Surname, save_student[new_count].RecordBookNum, save_student[new_count].Faculty, save_student[new_count].Group);
	
	} else{
	
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

        if(!pfile){

                perror("Error opened");
                exit(1);
        }

        /*if (count_student == 0) {

                fclose(pfile);

                return all_students;

        }*/
        if(count_student > 0) {

                all_students = (struct student*)realloc(all_students, count_student * sizeof(struct student));
                int counter_help = 0;

                while(counter_help < count_student){
        
                        fscanf(pfile, "%99s%d%99s%99s", all_students[counter_help].Surname, &all_students[counter_help].RecordBookNum, all_students[counter_help].Faculty, all_students[counter_help].Group);
        
                        counter_help++;
    
                }                
       
                //fclose(pfile);

   		//return all_strudents;
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
        scanf("%d", &new_student->RecordBookNum);
        printf("Faculty: ");
        scanf("%99s", new_student->Faculty);
        printf("Group: ");
        scanf("%99s", new_student->Group);

        new_student = new_student - count_student;

        save(new_student, count_student, 0, path);

        printf("The student has been successfully added");

}

void print_table(const char *path){

        FILE *pfile = fopen(path, "r");

        if (!pfile) {
                perror("Error opened");
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

        printf("Enter the last name of the student you want to remove from the table: ");
        char surname[100];
        scanf("%99s", surname);

        int index_del = 0;
	printf("%d", count_student);

        for(int i = 0; i < count_student; i++){

                if (strcmp(all_students[i].Surname, surname) == 0){
			
			index_del = i;
			break;
                }

        }

        for(int i = index_del; i < count_student; i++){
			
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

        //printf("The deletion was completed successfully");

}

void edit(struct student *all_students, int count_students, const char *path){

	print_table(path);
	printf("Enter the last name of the student whose information you want to edit: ");
	
	char surname[100];
	scanf("%99s", surname);
	
	int index_edit = 0;

	for (int i = 0; i < count_students; i++){
	
		if (strcmp(all_students[i].Surname, surname) == 0) {
		
			index_edit = i;
			break;
		
		}
	
	}
	
	printf("Please indicate the field you want to change.\n(1)Surname\n(2)Record book number\n(3)Faculty\n(4)Group\nYour choise: ");
	
	int cmd = 0;
	scanf("%d", &cmd);

	printf("Enter a new value for the selected field: ");

	switch(cmd){

		case 1:

			scanf("%99s", all_students[index_edit].Surname);
			break;

		case 2:

			scanf("%d", &all_students[index_edit].RecordBookNum);
			break;

		case 3:
			
			scanf("%99s", all_students[index_edit].Faculty);
			break;

		case 4:
			
			scanf("%99s", all_students[index_edit].Group);
			break;
	
	}

	save(all_students, count_students, 1, path);

	/*for(int i = 0; i < count_students; i++){

                printf("Surnmae:%s\nRecord Book Number:%d\nFaculty:%s\nGroup:%s\n", all_students[i].Surname, all_students[i].RecordBookNum, all_students[i].Faculty, all_students[i].Group);

        }*/

}

void choise(const char *path){


        printf("Please select an action:\n1)Writing to a table;\n2)View table;\n3)Sort the table in ascending order by a given field;\n4)Search for an element in the table;\n5)Delete entry;\n6)Edit entry;\n7)\n8)Exit.\n");

        int cmd = 0;
        printf("Enter your choise:");
        scanf("%d", &cmd);

        while(cmd != 8){

                switch(cmd){

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
                }

                printf("\nEnter your choise: ");
                scanf("%d", &cmd);
        }


}

int main(){

        const char *path = "DB.txt";
        FILE *pfile = fopen(path, "a+");
        fclose(pfile);

        choise(path);

        return 0;

}
