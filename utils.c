/* PROJETO  ATAD 2019-20
* Identificacao dos Alunos:
*
*      Numero: 190221068 | Nome: André Dias
*      Numero: 190221029 | Nome: Tomás Barroso
*      Turma: EI-01
* Professora PL:
*
*       Patrícia Macedo
*/

/**
 * @file utils.c
 * @author André Dias, Tomás Barroso
 * @brief Provides implementation for auxiliary functions in utils.h
 * @version 0.1
 * @date 2020-06-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


int equalsStringIgnoreCase(char str1[], char str2[]) {
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

    printf("\n%d Patients were read!\n\n", countP); // feedback of how many reports were read
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
        
        Region r = createRegion(tokens[0], tokens[1], stringToNumber(tokens[2]), stringToNumber(tokens[3]));
        KeyString key = createKey(tokens[0]);
        free(tokens);
        int error_code = mapPut(*regions, key, r);
        
        if(error_code == MAP_FULL || error_code == MAP_UNKNOWN_KEY || error_code == MAP_NO_MEMORY || error_code == MAP_NULL)
        {
            printf("An error ocurred... Please try again... \n");
            return;
        }
        countP++;
    }

    printf("\n%d Regions were read!\n\n", countP); // feedback of how many reports were read
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

float stringToNumber(char *str) {
    char *initial, *final;
    final = initial = str;

    /* iterate over the strings with pointer arithmetic */
    while (*initial != '\0') {
        if (*initial != ',') {
            *final++ = *initial;
        }
        initial++;
    }
    
    *final = '\0'; // empty final string when done
    return atof(str);
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

void printTopNReleased(PtList list, int n, int listSize) { 
    int ranks[n];
    int size = 0;
    int rank = 0, days, maxdays;
    Patient patient, patientmax;

    /* nested for loop to iterate n times over the list */
    for(int j = 0; j < n; j++) {
    listGet(list, 0, &patientmax);
    for(int i = 0; i < listSize; i++) {
        listGet(list, i, &patient);
        if(getStatus(patient) == 'r') { // check if patient is released
            maxdays = getNumberOfInfectedDays(patientmax);
            days = getNumberOfInfectedDays(patient);
            if(maxdays < days && isRankIgnored(i, ranks, size) == 0) { // check if days are bigger than current max days and if rank is already taken
                patientmax = patient;
                rank = i;
                
            }
        }
    }
    ranks[j] = rank; // add new max rank to the array (to be ignored in nested for loop)
    size++;
    printPatient(patientmax);
    }
}

int getOldestAgeBySex(PtList list, char *sex, int listSize) {
    Patient patient, patientmax;
    int age, maxage;
    listGet(list, 0, &patientmax);
    for(int i = 0; i < listSize; i++) {
        listGet(list, i, &patient);
        if(getStatus(patient) != 'd' && strcmp(patient.sex, sex) == 0 && patient.birthYear != -1) { // check if patient is dead, if sex aligns with input and has valid birtyear
            maxage = getAge(patientmax);
            age = getAge(patient);
            if(maxage < age) {
                patientmax = patient;
                maxage = age;
            }
        }
    }
    return maxage;
}

void showStatusStatsByAge(PtList list, int listSize, int lowerlim, int upperlim) {
    int isolated = 0, deceased = 0, released = 0;
    Patient p;
    if (upperlim > 89) upperlim = 999; // anything above 89 is its own category
    
    /* iterate over the list to count patients based on status */
    for(int i = 0; i < listSize; i++) {
        listGet(list, i, &p);
        int age = getAge(p);
        if(age >= lowerlim && age <= upperlim) {
            switch (getStatus(p)) {
            case 'i':
                isolated++;
                break;
            
            case 'd':
                deceased++;
                break;

            case 'r':
                released++;
                break;

            default:
                break;
            }
        }
    }

    /* print the stats in a line with appropriate format */
    if (upperlim > 89){
        printf("\n[%-2d - ...] ", lowerlim);
    } else {
        printf("\n[%-2d - %-3d] ", lowerlim, upperlim);
        }

    printf("| %-8d | %-8d | %-8d |", isolated, deceased, released);
}

int isRankIgnored(int rank, int *arr, int size) {
    for(int i = 0; i < size; i++) {
        if(rank == arr[i]) return 1;
    }
    return 0;
}

void showGrowth(PtList list, Date date, int listSize) {
    time_t current = time(NULL);
    time_t input = dateToTimeT(date);

    if(input > current || dateUnknown(date) != 0) {
        printf("Invalid date");
        return;
    }

    time_t inputbefore = input - 86400;
    int deathsbefore = 0, isolatedbefore = 0, deaths = 0, isolated = 0;
    Patient p;
    for(int i = 0; i < listSize; i++) {
        listGet(list, i, &p);
        if(dateUnknown(p.confirmedDate) == 0) {
            time_t dateP = dateToTimeT(p.confirmedDate);
            if(input >= dateP) isolated++;
            if(inputbefore >= dateP) isolatedbefore++;
        }

        if(dateUnknown(p.deceasedDate) == 0) {
            time_t dateP = dateToTimeT(p.deceasedDate);
            if(input >= dateP) deaths++;
            if(inputbefore >= dateP) deathsbefore++;
        }
    }
    struct tm prevDate = *localtime(&inputbefore);
    
    if(deaths == 0 || isolated == 0) {
        printf("There is no record for date: ");
        printDate(date);
        printf("\n");
        return;
    }
    
    if(deathsbefore == 0 || isolatedbefore == 0) {
        printf("There is no record for date: %d/%d/%d\n", prevDate.tm_mday, prevDate.tm_mon + 1, prevDate.tm_year + 1900);
        return;
    }
    
    printf("Date: %d/%d/%d\n", prevDate.tm_mday, prevDate.tm_mon + 1, prevDate.tm_year + 1900);

    printf("Number of deaths: %d\n", deathsbefore);
    printf("Number of infected: %d\n", isolatedbefore);

    printf("\nDate: ");
    printDate(date);
    printf("\n");

    printf("Number of deaths: %d\n", deaths);
    printf("Number of infected: %d\n", isolated);

    double deathRate = round(getRate(deaths, deathsbefore) * 100);
    double infectedRate = round(getRate(isolated, isolatedbefore) * 100);

    printf("\nRate of new infected: %.0f%%", infectedRate);
    printf("\nRate of new deaths: %.0f%%", deathRate);
}

double getRate(double val1, double val2) {
    return (val1-val2)/val2;
}

double getAverage(double val1, double val2) {
    return val1/val2;
}

void orderStringArrAlphaBBsort(char* strings[], int size){
    for(int i = 1; i < size; i++) {
        for(int j = 0; j < size - i; j++) {
            if(strcmp(strings[j], strings[j+1]) > 0) {
                char tmp[20];
                strcpy(tmp, strings[j]);
                strcpy(strings[j], strings[j+1]);
                strcpy(strings[j+1], tmp);
            }
        }
    }
}

int stringIsRepeated(char* strings[], int size, char* string) {
    int repeated = 0;
    for(int j = 0; j < size; j++) {
        if(strcmp(strings[j], string) == 0){
            repeated = 1;
            break;
        }
    }
    return repeated;
}