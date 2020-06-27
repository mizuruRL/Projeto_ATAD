#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"

void menu() {
	printf("\n===================================================================================");
	printf("\n                          PROJECT: COVID-19                    ");
	printf("\n===================================================================================");
	printf("\nA. Base Commands (LOAD, LOADR,CLEAR).");
	printf("\nB. Simple Indicators and searchs (AVERAGE, FOLLOW, MATRIX, OLDEST, RELEASED, SEX, SHOW, TOP5).");
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