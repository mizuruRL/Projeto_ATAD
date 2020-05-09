#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "patient.h"

Patient createPatient(int id, char* sex, int birthYear, char* country, char* region, char* infectionReason, int infectedBy, Date confirmedDate, Date releasedDate, Date deceasedDate, char* status){
    Patient patient = {id,sex,birthYear,country,region,infectionReason,infectedBy,{confirmedDate.day,confirmedDate.month,confirmedDate.year},{releasedDate.day,releasedDate.month,releasedDate.year},{deceasedDate.day,deceasedDate.month,deceasedDate.year},status};
    return patient;
}

void printPatient(Patient p){

    printf("###############  Patient  ###############\n\n");
    printf("ID: \n",p.id);
    printf("SEX: \n",p.sex);
    printf("AGE: \n",getAge(p));
    printf("COUNTRY/REGION: %s/%s \n",p.country,p.region);
    printf("INFECTION REASON: \n",p.infectionReason);
    printf("STATE: \n",p.status);
    printf("NUMBER OF DAYS WITH ILLNESS: %d\n\n",getNumberOfInfectedDays(p));
    printf("#########################################\n");
}
int getAge(Patient p){
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);
    int currentYear = local->tm_year + 1900;
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