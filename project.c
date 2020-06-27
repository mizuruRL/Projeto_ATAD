#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "project.h"

typedef char String[255];

void menu(){
    String command;
	int quit = 0;

	setlocale(LC_ALL, "PT");
	while (!quit) {
		
		printCommandsMenu();
		fgets(command, sizeof(command), stdin);
		/* descartar 'newline'. Utilizar esta técnica sempre que for lida uma
		* string para ser utilizada, e.g., nome de ficheiro, chave, etc.. */
		command[strlen(command) - 1] = '\0';

		if (equalsStringIgnoreCase(command, "QUIT")) {
			quit = 1; /* vai provocar a saída do interpretador */				
		}
		else if (equalsStringIgnoreCase(command, "LOADP")) {
			commandLoadP();
		}
		else if (equalsStringIgnoreCase(command, "LOADR")) {
			/* invocação da função responsável pela respetiva
			funcionalidade. Remover printf seguinte após implementação */
			printf("Comando LOADR nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "CLEAR")) {
			printf("Comando CLEAR nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "AVERAGE")) {
			printf("Comando AVERAGE nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "FOLLOW")) {
			printf("Comando FOLLOW nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "SEX")) {
			printf("Comando SEX nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "SHOW")) {
			printf("Comando SHOW nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "TOP5")) {
			printf("Comando TOP5 nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "OLDEST")) {
			printf("Comando OLDEST nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "GROWTH")) {
			printf("Comando GROWTH nao implementado.\n");
		}	
		else if (equalsStringIgnoreCase(command, "MATRIX")) {
			printf("Comando MATRIX nao implementado.\n");
		}
		else if (equalsStringIgnoreCase(command, "REGIONS")) {
			printf("Comando REGIONS nao implementado.\n");
		}	
		else if (equalsStringIgnoreCase(command, "REPORT")) {
			printf("Comando REPORT nao implementado.\n");
		}
		else {
			printf("%s : Comando não encontrado.\n", command);
		}
	}
}

int equalsStringIgnoreCase(char str1[], char str2[]) {
	/* Apenas faz uma comparacao utilizando o strcmp.
	* Necessita de modificacao para obter uma comparacao
	* 'case insensitive' */
	return (strcasecmp(str1, str2) == 0);
}

void printCommandsMenu() {
	printf("\n===================================================================================");
	printf("\n                          PROJECT: COVID-19                    ");
	printf("\n===================================================================================");
	printf("\nA. Base Commands (LOAD, LOADR,CLEAR).");
	printf("\nB. Simple Indicators and searchs (AVERAGE, FOLLOW, MATRIX, OLDEST, RELEASED, SEX, SHOW, TOP5).");
	printf("\nC. Advanced indicator (REGIONS, REPORTS)");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}


void commandLoadP(){

    char filename[50];
    char file[7] = "files/";
    printf("Please chose file: ");
    scanf("%s",filename);
    strcat(file,filename);
    strcat(file,".csv");

    importFromFile(file);
    menu();
}

void commandLoadR(){
    
}

void commandClear(){
    
}

void commandQuit(){
    
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

char** split(char *string, int nFields, const char *delim) {
    char **tokens = (char**) malloc(sizeof(char*) * nFields);
    int index = 0;
    int len = strlen(string);
    tokens[index++] = &string[0];
    for(int i=0; i < len; i++) {
        if( string[i] == delim[0] ) {
            string[i] = '\0';
            if( i < len - 1 ) {
                tokens[index++] = &string[i] + 1;
            }           
        }
    }
    return tokens;
}

void importFromFile(char* filename){

    FILE *f = NULL;

	f = fopen(filename, "r");

	if (f == NULL) {
		printf("An error ocurred... the file %s  was not found\n", filename);
		return;
	}

	char nextline[1024];

	int countRegistrees = 0;
	bool firstLine = true;

	while (fgets(nextline, sizeof(nextline), f)) {
		if (strlen(nextline) < 1)
			continue;

		/*As the first line of the file contains the names of the fields it should be ignored*/
		if (firstLine){
			firstLine = false;
			continue;
		} 

        if(strcmp(filename,"files/patients.csv")){
        
            char **tokens = split(nextline, 11, ";");
		

        Date dates[3];
            for(int i = 7; i < 10; i++){
                int count = 0;
                if(tokens[i] != ""){
                    char **dateToken = split(tokens[i],3,"/");

                    Date date = {atoi(dateToken[0]),atoi(dateToken[1]),atoi(dateToken[2])};
                    dates[count] = date;
                    count++;
                    free(dateToken);
                }else{
                    Date date = {0,0,0};
                    dates[count] = date;
                }
            }


		Patient patient = createPatient(atoi(tokens[0]), tokens[1], atoi(tokens[2]), tokens[3], tokens[4], tokens[5], atoi(tokens[6]), 
        dates[0], dates[1], dates[2], tokens[10]);
            

            
            free(tokens); // release of the memory alocated in function split
        }

        if(strcmp(filename,"files/regions.csv")){
            PtMap regionsMap = mapCreate(10);
            char **tokens = split(nextline, 4, ";");
                
            Region region = {tokens[0],tokens[1],atoi(tokens[2]),atoi(tokens[3])};

                
            free(tokens); // release of the memory alocated in function split
        }

		countRegistrees++;
	}

	
	printf("\n\n> %d  Reports were read!\n\n", countRegistrees);
	fclose(f);

}

void insertPatient(PtMap regionsMap, Patient patient, int rank){
        PtList patientsList = listCreate(10);
        int error_code = listAdd(&patientsList, rank, patient);

        if (error_code == LIST_FULL ||error_code == LIST_INVALID_RANK || 
            error_code == LIST_NO_MEMORY || error_code == LIST_NULL){
            printf("An error ocurred... Please try again... \n");
            return;
        }

        listDestroy(&patientsList);
}

void insertRegions(Region region, char* key){

    int error_code = mapPut(&regionsMap,key,region);

    if (error_code == MAP_FULL || error_code == MAP_NO_MEMORY || error_code == LIST_NULL){
            printf("An error ocurred... Please try again... \n");
            return;
    }
}

