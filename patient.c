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

    printf("###############  Patient  ###############\n\n");
    printf("ID: %ld\n",p.id);
    printf("SEX: %s\n",p.sex);
    printf("AGE: %d\n",getAge(p));
    printf("COUNTRY/REGION: %s/%s \n",p.country,p.region);
    printf("INFECTION REASON: %s\n",p.infectionReason);
    printf("STATE: %s\n",p.status);
    printf("NUMBER OF DAYS WITH ILLNESS: 1\n\n");
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

int getNumberOfInfectedDays(Patient p){
    int totalDays = 0;
    time_t now;
    struct tm *local = localtime(&now);
    int currentDay = local->tm_mday;
    int currentMonth = local->tm_mon;
    int currentYear = local->tm_year + 1900;
    if(p.deceasedDate.day == 0 && p.deceasedDate.month == 0 && p.deceasedDate.year == 0){

        if(p.releasedDate.day == 0 && p.releasedDate.month == 0 && p.releasedDate.year == 0){

            Date old = {p.confirmedDate.day,p.confirmedDate.month,p.confirmedDate.year};
            Date recent = {currentDay,currentMonth,currentYear};
            totalDays = getDifference(old,recent);

        }else{

            Date old = {p.confirmedDate.day,p.confirmedDate.month,p.confirmedDate.year};
            Date recent = {p.releasedDate.day,p.releasedDate.month,p.releasedDate.year};
            totalDays = getDifference(old,recent);
            
        }

    }else{

        Date old = {currentDay,currentMonth,currentYear};
        Date recent = {p.deceasedDate.day,p.deceasedDate.month,p.deceasedDate.year};
        totalDays = getDifference(old,recent);

    }
    return totalDays;
}

int getDifference(Date old, Date recent){ 
    int countDays = 0;
    int countMonths = 0;
    int countYears = 0;

    countYears = recent.year - old.year;
    countMonths = recent.month - old.month;
    countDays = recent.day - old.day; 

    return countYears + countMonths + countDays;
}

int stringIsBlank(char *str) {
    int i = 0;
    while (str[i] != '\0')
    {
        if(str[i] != ' ')
        return 0;
        i++;
    }
    return 1;
}