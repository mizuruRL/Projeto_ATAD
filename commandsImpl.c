/* PROJETO  ATAD 2019-20
* Identificacao dos Alunos:
*
*      Numero: 190221068 | Nome: André Dias
*      Numero: 190221029 | Nome: Tomás Barroso
* Professora PL:
*
*       Patrícia Macedo
*/


/**
 * @file commandsImpl.c
 * @author André Dias, Tomás Barroso
 * @brief Implements the commands in commandsImpl.h
 * @version 0.1
 * @date 2020-06-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commandsImpl.h"

void menu() {
	printf("\n===================================================================================");
	printf("\n                          PROJECT: COVID-19                    ");
	printf("\n===================================================================================");
	printf("\nA. Base Commands (LOADP, LOADR, CLEAR).");
	printf("\nB. Simple Indicators and searchs (AVERAGE, FOLLOW, MATRIX, OLDEST, GROWTH, SEX, SHOW, TOP5)");
	printf("\nC. Advanced indicator (REGIONS, REPORTS)");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}


void commandLoadP(PtList *patients) {
    importPatientsFromFile("files/patients.csv", patients);
}

void commandLoadR(PtMap *regions) {
    importRegionsFromFile("files/regions.csv", regions);
}

void commandClear(PtList patients, PtMap regions) {
	int psize = 0;
	int msize = 0;
	listSize(patients, &psize);
	mapSize(regions, &msize);
	listClear(patients);
	mapClear(regions);
	printf("%d records discarded from <Patients %d | Regions %d>", psize + msize, psize, msize);
}

int commandQuit(PtList *patients, PtMap *regions) {
    if(patients != NULL) {
        listDestroy(patients);
    }
    if(regions != NULL) {
	    mapDestroy(regions);
    }
    return 1;
}

void commandAverage(PtList list){
    int patientsListSize = 0,countDeceasedAges = 0,countDeceasedTotal = 0,
    countReleasedAges = 0,countReleasedTotal = 0,countIsolatedAges = 0,countIsolatedTotal = 0, age = 0;

    int errorcode = listSize(list,&patientsListSize);
    
    if(errorcode == LIST_NULL) {
        printf("Patients list wasn't loaded");
        return;
    }

    if(patientsListSize == 0) {
        printf("Patients list is empty");
        return;
    }

	Patient patient;
    for(int i = 0; i < patientsListSize; i++){
        
        listGet(list,i,&patient);
		age = getAge(patient);
        if(age != -1){
            switch (getStatus(patient)) {
            case 'r':
                countReleasedTotal++;
                countReleasedAges+=getAge(patient);
                break;
            
            case 'd':
                countDeceasedTotal++;
                countDeceasedAges+=getAge(patient);
                break;

            case 'i':
                countIsolatedTotal++;
                countIsolatedAges+=getAge(patient);
                break;
            default:
                break;
            }
        }
    }
    
    printf("\nAverage Age for deceased patients: %.0f\n", round(getAverage(countDeceasedAges, countDeceasedTotal)));
    printf("\nAverage Age for released patients: %.0f\n", round(getAverage(countReleasedAges,countReleasedTotal)));
    printf("\nAverage Age for isolated patients: %.0f\n", round(getAverage(countIsolatedAges, countIsolatedTotal)));
}

void commandFollow(PtList list, long int id){
    Patient patient;
    int errorcode = listGetById(list,id,&patient);
    
    if(errorcode == LIST_NULL) {
        printf("Patients list wasn't loaded");
        return;
    }

    if(errorcode == LIST_EMPTY) {
        printf("Patients list is empty");
        return;
    }

    if(errorcode == LIST_INVALID_RANK){
        printf("Id not found");
        return;
    }

    printf("\nFollowing Patient: ID:%ld, SEX: %s, AGE: %d, COUNTRY/REGION: %s / %s, STATE: %s\n",patient.id,patient.sex,getAge(patient),patient.country,patient.region,patient.status);
        
    long int idContamined = patient.infectedBy;
    z:
    if(idContamined > 0){
        errorcode = listGetById(list,idContamined,&patient);
            
        if(errorcode != LIST_INVALID_RANK) {
            printf("\nContaminated by Patient: ID:%ld, SEX: %s, AGE: %d, COUNTRY/REGION: %s / %s, STATE: %s",patient.id,patient.sex,getAge(patient),patient.country,patient.region,patient.status);
        idContamined = patient.infectedBy;
        } else {
            printf("Contaminated by patient: %ld : does not exist record\n", idContamined);
            idContamined = -1;
        }
        goto z;
    }else{
        printf("Contaminated by Unknown\n");
    }
}

void commandSex(PtList list){
    int size = 0,maleCount = 0,femaleCount = 0,unknownCount = 0;
    int errorcode = listSize(list,&size);
    Patient patient;

    if(errorcode == LIST_NULL) {
        printf("Patients list wasn't loaded");
        return;
    }

    if(size == 0) {
        printf("Patients list is empty");
        return;
    }

    for(int i = 0; i < size; i++){
        listGet(list,i,&patient);
        if(strcmp(patient.sex,"male") == 0){
            maleCount++;
        }
        else if(strcmp(patient.sex,"female") == 0){
            femaleCount++;
        }
        else{
            unknownCount++;
        }
    }

    printf("\nPercentage of Females: %.0f%%",((double)femaleCount/(double)size)*100);
    printf("\nPercentage of Males: %.0f%%",((double)maleCount/(double)size)*100);
    printf("\nPercentage of unknown: %.0f%% ",((double)unknownCount/(double)size)*100);
    printf("\nTotal of patients: %d\n",size);

}

void commandShow(PtList list, long int id){
    int errorcode = 0;
    Patient patient;
    errorcode = listGetById(list, id, &patient);

    if(errorcode == LIST_NULL) {
        printf("Patients list wasn't loaded");
        return;
    }

    if(errorcode == LIST_EMPTY) {
        printf("Patients list is empty");
        return;
    }

    if(errorcode == LIST_INVALID_RANK){
        printf("Id not found");
        return;
    }

    printPatient(patient);
}

void commandTop5(PtList list){
    int lSize = 0, size = 0;
    int errorCode = listSize(list, &lSize);

    if(errorCode == LIST_NULL) {
        printf("Patients list wasn't loaded");
        return;
    }

    if(lSize == 0) {
        printf("Patients list is empty");
        return;
    }

    printTopNReleased(list, 5, lSize);
}

void commandOldest(PtList list){
    int lSize = 0, size = 0, fAge, mAge;
    int errorCode = listSize(list, &lSize);
    Patient p;

    if(errorCode == LIST_NULL) {
        printf("Patients list wasn't loaded");
        return;
    }

    if(lSize == 0) {
        printf("Patients list is empty");
        return;
    }

    mAge = getOldestAgeBySex(list, "male", lSize);
    fAge = getOldestAgeBySex(list, "female", lSize);
    int count = 1;
    printf("\nMales:\n");
    for(int i = 0; i < lSize; i++) {
        listGet(list, i, &p);
        int age = getAge(p);
        if(age == mAge && strcmp(p.sex, "male") == 0) {
            printf("%d- ", count);
            printf("ID: %ld, SEX: %s, AGE: %d, COUNTRY/REGION: %s / %s, STATE: %s\n", p.id, p.sex, age, p.country, p.region, p.status);
            count++;
        }
    }

    count = 1;
    printf("Females:\n");
    for(int i = 0; i < lSize; i++) {
        listGet(list, i, &p);
        int age = getAge(p);
        if(age == fAge && strcmp(p.sex, "female") == 0) {
            printf("%d- ", count);
            printf("ID: %ld, SEX: %s, AGE: %d, COUNTRY/REGION: %s / %s, STATE: %s\n", p.id, p.sex, age, p.country, p.region, p.status);
            count++;
        }
    }
}

void commandGrowth(PtList list, char* date){
    int size = 0;
    int errorCode = listSize(list, &size);

    if(errorCode == LIST_NULL) {
        printf("Patients list wasn't loaded");
        return;
    }

    if(size == 0) {
        printf("Patients list is empty");
        return;
    }
    Date d = stringToDate(date);
    
    showGrowth(list, d, size);
}

void commandMatrix(PtList list){
    int size = 0;
    int errorCode = listSize(list, &size);

    if(errorCode == LIST_NULL) {
        printf("Patients list wasn't loaded");
        return;
    }

    if(size == 0) {
        printf("Patients list is empty");
        return;
    }
    
    Patient p;
    int upperLim = 15, lowerLim = 0;
    printf("%19s%11s%11s", "Isolated", "Deceased", "Released");
    for(int i = 0; i < 6; i++) {
        showStatusStatsByAge(list, size, lowerLim, upperLim);
        lowerLim = upperLim + 1;
        upperLim += 15;
    }
}

void commandRegions(PtList list, PtMap map){
    int lSize = 0;
    int mSize = 0;
    int arrSize = 0;
    int lerrorCode = listSize(list, &lSize);
    int merrorCode = mapSize(map, &mSize);

    if(lerrorCode == LIST_NULL) {
        printf("Patients list wasn't loaded");
        return;
    }

    if(lSize == 0) {
        printf("Patients list is empty");
        return;
    }

    if(merrorCode == MAP_NULL) {
        printf("Regions list wasn't loaded");
        return;
    }

    if(mSize == 0) {
        printf("Regions list is empty");
        return;
    }

    char **str = (char**)malloc(20*sizeof(char*)); //Allocate memory for string array to hold region names
     for(int i = 0; i < 20; i++){
        str[i] = (char*)malloc(50*sizeof(char)); //Allocate memory for each string
    }
    
    Patient patient;
    MapValue mapValue;
    KeyString key;
    for(int i = 0; i < lSize; i++){
        listGet(list,i,&patient);
        if(getStatus(patient) == 'i'){ //Check if patient is isolated (still infected)
            key = createKey(patient.region); //Get the key from the patient
            mapGet(map, key, &mapValue); 
            if(!stringIsRepeated(str, arrSize, key.content)) { //Check if the region name already exists inside the array
                strcpy(str[arrSize],key.content);
                arrSize++;
            }
        }
    }

    orderStringArrAlphaBBsort(str, arrSize); //Sort the region names array alphabetically

    printf("\nActive regions (alphabetically): \n\n"); //print the region names
    for(int i = 0; i < arrSize; i++){
        key = createKey(str[i]);
        mapKeyPrint(key);
    }
    
    for(int i = 0; i < 20; i++){ //Free memory allocated from the strings
        free(str[i]);
    }
    free(str);//Free the array pointer
}

void commandReport(PtMap map, PtList list){
    int mSize = 0, lSize = 0;
    int mErrorCode = mapSize(map,&mSize);
    int lErrorCode = listSize(list,&lSize);

    if(lErrorCode == LIST_NULL) {
        printf("Patients list wasn't loaded");
        return;
    }

    if(lSize == 0) {
        printf("Patients list is empty");
        return;
    }

    if(mErrorCode == MAP_NULL) {
        printf("Regions list wasn't loaded");
        return;
    }

    if(mSize == 0) {
        printf("Regions list is empty");
        return;
    }
    
    FILE * fPtr;

    fPtr = fopen("files/report.txt", "w");

    if(fPtr == NULL){
        /* File not created hence exit */
        printf("\nReport not created.\n\n");
        return;
    }else{
        printf("\nReport created.\n\n");
    }

    int deaths = 0, infected = 0;
    double mortality = 0, incidentRate = 0, lethality = 0;

    MapKey* keys = mapKeys(map);

    Patient patient;
    for(int i = 0; i < mSize; i++) {
        for(int j = 0; j < lSize; j++) {
            listGet(list, j, &patient);
            if(strcmp(keys[i].content, patient.region) == 0) {
                switch (getStatus(patient)) {
                case 'd':
                    deaths++;
                    break;
                
                case 'i':
                    infected++;
                    break;

                default:
                    break;
                }
            }
        }
        MapValue value;
        mapGet(map,keys[i],&value);
        mortality = ((double)deaths/(double)(value.population) * 10000);
        lethality = ((double)deaths/(double)lSize)* 100;
        incidentRate = ((double)infected/(double)value.population) * 100;

        if(mortality == 0 && lethality == 0 && incidentRate == 0) {
            printf("Unknown region (no population data)\n");
        } else {
            printf("%s Mortality: %.3f %%  Incident Rate: %.3f %%  Lethality: %.3f %%\n",keys[i].content, mortality, incidentRate, lethality);
            fprintf(fPtr,"%s Mortality: %.3f %%  Incident Rate: %.3f %%  Lethality: %.3f %%\n",keys[i].content, mortality, incidentRate, lethality);
        }
    }
    free(keys);
    fclose(fPtr);
}