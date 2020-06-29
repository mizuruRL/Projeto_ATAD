#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"

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
            if(strcmp(patient.status,"released\n") == 0){
                        countReleasedTotal++;
                        countReleasedAges+=getAge(patient);
            }else if(strcmp(patient.status,"isolated\n") == 0){
                        countIsolatedTotal++;
                        countIsolatedAges+=getAge(patient);
            }else if(strcmp(patient.status,"deceased\n") == 0){
                        countDeceasedTotal++;
                        countDeceasedAges+=getAge(patient);
            }
        }
    }
    
    printf("\nAverage Age for deceased patients: %.0f\n",(double)countDeceasedAges/(double)countDeceasedTotal);
    printf("\nAverage Age for released patients: %.0f\n",(double)countReleasedAges/(double)countReleasedTotal);
    printf("\nAverage Age for isolated patients: %.0f\n",(double)countIsolatedAges/(double)countIsolatedTotal);
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

void commandGrowth(){
    
}

void commandMatrix(){
    
}

void commandRegions(PtList list, PtMap map){
    int lSize = 0;
    int mSize = 0;
    
    int lerrorCode = listSize(list, &lSize);

    if(lerrorCode == LIST_NULL) {
        printf("Patients list wasn't loaded");
        return;
    }

    if(lSize == 0) {
        printf("Patients list is empty");
        return;
    }

    PtMap newMap = mapCreate(10);
    char* str[20];

    for(int i = 0; i < lSize; i++){
        Patient patient;
        listGet(list,i,&patient);
        if(strcmp(patient.status,"isolated") == 0){
            MapValue mapValue;
            KeyString key = createKey(patient.region);
            mapGet(map, key, &mapValue);
            strcpy(str[i],key.content);
            mSize++;
        }
    }

    orderAlphabetically(str,mSize);

    for(int i = 0; i < mSize; i++){
         KeyString key = createKey(str[i]);
         MapValue mapValue;
         mapGet(map,key,&mapValue);
        mapPut(newMap,key,mapValue);
    }

    mapPrint(newMap);
    mapDestroy(&newMap);
}

void commandReport(){
    
}