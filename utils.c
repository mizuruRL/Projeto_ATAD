#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


int equalsStringIgnoreCase(char str1[], char str2[]) {
	/* Apenas faz uma comparacao utilizando o strcmp.
	* Necessita de modificacao para obter uma comparacao
	* 'case insensitive' */
	return (strcasecmp(str1, str2) == 0);
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

void importPatientsFromFile(char *filename, PtList *patients) {
    FILE *f = NULL;

    f = fopen(filename, "r");

    if(f == NULL)
    {
        printf("An error ocurred... It was not possible to open the file %s ...\n", filename);
        return;
    }

    char nextline[1024];

    int countP = 0;
    bool firstLine = true;

    *patients = listCreate(10);

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

        char **tokens = split(nextline, 11, ";");
    
        Patient p;
        p = createPatient(atol(tokens[0]), tokens[1], atoi(tokens[2]), tokens[3], tokens[4], tokens[5], atol(tokens[6]), stringToDate(tokens[7]), stringToDate(tokens[8]), stringToDate(tokens[9]), tokens[10]);

        free(tokens);

        int error_code = listAdd(*patients, countP, p);

        if(error_code == LIST_FULL || error_code == LIST_INVALID_RANK || error_code == LIST_NO_MEMORY || error_code == LIST_NULL)
        {
            printf("An error ocurred... Please try again... \n");
            return;
        }
        
        countP++;
    }

    printf("\n%d Patients were read!\n\n", countP);
    fclose(f);
}

void importRegionsFromFile(char *filename, PtMap *regions) {
    FILE *f = NULL;

    f = fopen(filename, "r");

    if(f == NULL)
    {
        printf("An error ocurred... It was not possible to open the file %s ...\n", filename);
        return;
    }

    char nextline[1024];

    int countP = 0;
    bool firstLine = true;

    *regions = mapCreate(10);

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

        char **tokens = split(nextline, 4, ";");
        //not working
        int error_code = mapPut(*regions, tokens[0], createRegion(tokens[0], tokens[1], stringToNumber(tokens[2], 1), (int)stringToNumber(tokens[3],getCommas(tokens[3]))));
        free(tokens);
        if(error_code == MAP_FULL || error_code == MAP_UNKNOWN_KEY || error_code == MAP_NO_MEMORY || error_code == MAP_NULL)
        {
            printf("An error ocurred... Please try again... \n");
            return;
        }
        countP++;
    }

    printf("\n%d Regions were read!\n\n", countP);
    fclose(f);
}

Date stringToDate(char *str) {
    Date date;
    if(strcmp(str, "")){
        char **dateToken = split(str,3,"/");
        date = createDate(atoi(dateToken[0]),atoi(dateToken[1]),atoi(dateToken[2]));
        free(dateToken);
    }else{
        date = createDate(0,0,0);
    }
    return date;
}

float stringToNumber(char *str, int nComma) {
    char number[50] = "0";
    char **tokens = split(str,nComma + 1,",");
    for(int i = 0; i < nComma + 1; i++) {
        if(tokens[i] != NULL) {
            strcat(number, tokens[i]);
        }
    }
    free(tokens);
   
    return atof(number);
}

int getCommas(char *str) {
    int i = 0;
    int commas = 0;
    while(str[i] != '\n') {
        if(str[i] == ',') commas++;
        i++;
    }
    return commas;
}

int listGetById(PtList list, long int id, ListElem *ptElem){
    int size;
    int error = listSize(list,&size);
    if(error == LIST_NULL) {
        return error;
    }

    if(size == 0) {
        error = LIST_EMPTY;
        return error;
    }
    
    for(int i = 0; i < size; i++){
        Patient patient;
        listGet(list,i,&patient);
        if(patient.id == id){
            *ptElem = patient;
            return LIST_OK;
        }
    }

    return LIST_INVALID_RANK;
}