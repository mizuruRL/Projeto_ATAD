#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "project.h"
#include "patient.h"
#include "listElem.h"

void printCommandsMenu() {
	printf("\n===================================================================================");
	printf("\n                          PROJECT: COVID-19                                        ");
	printf("\n===================================================================================");
	printf("\nA. Base Commands (LOAD, LOADR,CLEAR).");
	printf("\nB. Simple Indicators and searchs (AVERAGE, FOLLOW, MATRIX, OLDEST, RELEASED, SEX, SHOW, TOP5).");
	printf("\nC. Advanced indicator (REGIONS, REPORTS)");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}

int equalsStringIgnoreCase(char* str1, char* str2) {
	return (strcasecmp(str1, str2) == 0);
}

void clean(){
    system("clear");
}

void appStart(){
    typedef char String[255];

    String command;
	int quit = 0;

	setlocale(LC_ALL, "PT");
	while (!quit) {
		
		printCommandsMenu();
		fgets(command, sizeof(command), stdin);
		command[strlen(command) - 1] = '\0';
        
		if (equalsStringIgnoreCase(command, "QUIT")) {
			quit = 1;
			printf("Goodbye!\n");			
		}
		else if (equalsStringIgnoreCase(command, "LOAD")) {
			commandLoad();
		}
		else if (equalsStringIgnoreCase(command, "LOADR")) {
			commandLoadR();
		}
		else if (equalsStringIgnoreCase(command, "CLEAR")) {
			commandClear();
		}
		else if (equalsStringIgnoreCase(command, "AVERAGE")) {
			commandAverage();
		}
		else if (equalsStringIgnoreCase(command, "FOLLOW")) {
			commandFollow();
		}
		else if (equalsStringIgnoreCase(command, "SEX")) {
			commandSex();
		}
		else if (equalsStringIgnoreCase(command, "SHOW")) {
			commandShow();
		}
		else if (equalsStringIgnoreCase(command, "TOP5")) {
			commandTop5();
		}
		else if (equalsStringIgnoreCase(command, "OLDEST")) {
			commandOldest();
		}
		else if (equalsStringIgnoreCase(command, "GROWTH")) {
			commandGrowth();
		}	
		else if (equalsStringIgnoreCase(command, "MATRIX")) {
			commandMatrix();
		}
		else if (equalsStringIgnoreCase(command, "REGIONS")) {
			commandRegions();
		}	
		else if (equalsStringIgnoreCase(command, "REPORT")) {
			commandReport();
		}
		else {
			printf("%s : Not found.\n", command);
		}
	}
}

void commandLoad(){
	PtList list;
	clean();
	char filename[100];
	char format[5] = ".csv";
	printf("Please write only the file name\n> ");
    scanf("%s",filename);
	strcat(filename, format);
	importDataFromFile(filename,&list);
    /*clean();
    char filename[100];
    char format[5] = ".csv";
    printf("Please write only the file name\n> ");
    scanf("%s",filename);
    if(filename == "" || filename == NULL){
        printf("File not found!");
        appStart();
    }
    strcat(filename, format);
    FILE *file = fopen(filename, "r");
    char buf[1024];
    int row_count = 0;
    int field_count = 0;
    if(file){
	    int id;field_count = 0;
        row_count++;
    
        while (fgets(buf, 1024, file)) {
            row_count++;

            char *field = strtok(buf, ";");
            while (field) {
                char* info;
                for (int field_count = 0; field_count < 10; field_count++){
                    info[field_count] = field;
                }
                setupPatients(info);
            }
        }
    
    }else{
        printf("File not found!");
        appStart();
    }
    fclose(file); */
	
}

void commandLoadR(){
    
}

void commandClear(){
    
}

void commandAverage(){
    
}

void commandFollow(){
    
}

void commandSex(){
    
}

void commandShow(){
    
}

void commandTop5(){
    
}

void commandOldest(){
    
}

void commandGrowth(){

}

void commandMatrix(){
    
}

void commandRegions(){
    
}

void commandReport(){
    
}

void setupPatients(char* arr){
	int id = (int)arr[0];
    char* sex = arr[1];
    int birthYear = (int)arr[2];
    char* country = arr[3];
    char* region = arr[4];
    char* infectionReason = arr[5];
	int infectedBy = arr[6];
    Date confirmedDate = getDate(arr[7]);
    Date releasedDate = getDate(arr[8]);;
    Date deceasedDate = getDate(arr[9]);;
    char* status = arr[10];
	Patient patient = createPatient(id, sex, birthYear, country, region, infectionReason, infectedBy, confirmedDate, releasedDate, deceasedDate, status);

}

Date getDate(char* c){
	Date date;
	char *field = strtok(c, "/");
            while (field) {
                int day,month,year;
                for (int field_count = 0; field_count < 9; field_count++){
                    if(field_count == 0)day = field;
					if(field_count == 1)month = field;
					if(field_count == 2)year = field;
                }
                date = createDate(day,month,year);
            }
	return date;
}

char** split(char *string, int nFields, const char *delim)
{
    char **tokens = (char**) malloc(sizeof(char*) * nFields);

    int index = 0;

    char *token = (char*)strtok(string, delim);

    while(token)
    {
        tokens[index++] = token;
        token = strtok(NULL, delim);
    }

    return tokens;
}

void importDataFromFile(char *filename, PtList *listKR)
{
    FILE *f = NULL;

    f = fopen(filename, "r");

    if(f == NULL)
    {
        printf("An error ocurred... It was not possible to open the file %s ...\n", filename);
        return;
    }

    char nextline[1024];

    int countKR = 0;
    bool firstLine = true;

    *listKR = listCreate(10);

    while(fgets(nextline, sizeof(nextline), f))
    {
        if(strlen(nextline) < 1)
        {
            continue;
        }

        if(firstLine)
        {
            firstLine = false;
            continue;
        }

        char **tokens = split(nextline, 6, ";");



        Patient patient = createPatient(atoi(tokens[0]), atoi(tokens[1]), tokens[2], atoi(tokens[3]), atoi(tokens[4]), atoi(tokens[5]), atoi(tokens[6]), atoi(tokens[7]), atoi(tokens[9]), atoi(tokens[10]), atoi(tokens[11]));

        free(tokens);

        int error_code = listAdd(*listKR, countKR, kr);

        if(error_code == LIST_FULL || error_code == LIST_INVALID_RANK || error_code == LIST_NO_MEMORY || error_code == LIST_NULL)
        {
            printf("An error ocurred... Please try again... \n");
            return;
        }
        countKR++;
    }

    printf("\n%d Kahoot reports were read!\n\n", countKR);
    fclose(f);
}