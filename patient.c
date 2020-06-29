#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "patient.h"

Patient createPatient(long int id, char* sex, int birthYear, char* country, char* region, char* infectionReason, long int infectedBy, Date confirmedDate, Date releasedDate, Date deceasedDate, char* status){
    if(birthYear == 0) birthYear = -1;
    if(infectedBy == 0) infectedBy = -1;
    if(stringIsBlank(sex)) sex = "";
    if(stringIsBlank(country)) country = "";
    if(stringIsBlank(region)) region = "";
    if(stringIsBlank(infectionReason)) infectionReason = "";
    if(stringIsBlank(status)) status = "";
    Patient patient;
    patient.id = id;
    strcpy(patient.sex, sex);
    patient.birthYear = birthYear;
    strcpy(patient.country, country);
    strcpy(patient.region, region);
    strcpy(patient.infectionReason, infectionReason);
    patient.infectedBy = infectedBy;
    strcpy(patient.status, status); 
    patient.releasedDate = releasedDate;
    patient.confirmedDate = confirmedDate;
    patient.deceasedDate = deceasedDate;
    return patient;
}

void printPatient(Patient p){
    double days = getNumberOfInfectedDays(p);
    printf("###############  Patient  ###############\n\n");
    printf("ID: %ld\n",p.id);
    printf("SEX: %s\n",p.sex);
    printf("AGE: %d\n",getAge(p));
    printf("COUNTRY/REGION: %s/%s \n",p.country,p.region);
    printf("INFECTION REASON: %s\n",p.infectionReason);
    printf("STATE: %s\n",p.status);
    printf("NUMBER OF DAYS WITH ILLNESS: %.0f\n\n", days);
    printf("#########################################\n");
}

int getAge(Patient p){
    if(p.birthYear == -1) return p.birthYear;
    time_t now = time(NULL);
    struct tm local = *localtime(&now);
    int currentYear = local.tm_year + 1900;
    int age = currentYear - p.birthYear;
    return age;
}

double getNumberOfInfectedDays(Patient p){
    
    if(strcmp(p.status, "deceased\n") == 0) {
        time_t d1 = dateToTimeT(p.confirmedDate);
        time_t d2 = dateToTimeT(p.deceasedDate);
        return getDayDifference(d2, d1);
    }

     if(strcmp(p.status, "released\n") == 0) {
        time_t d1 = dateToTimeT(p.confirmedDate);
        time_t d2 = dateToTimeT(p.releasedDate);
        return getDayDifference(d2, d1);
    }

    if(strcmp(p.status, "isolated\n") == 0) {
        time_t now = time(NULL);
        time_t d1 = dateToTimeT(p.confirmedDate);
        return getDayDifference(now, d1);
    }
    return 0;
}

int stringIsBlank(char *str) {
    int i = 0;
    while (*str != '\0')
    {
        if(str[i] != ' ')
        return 0;
        i++;
    }
    return 1;
}