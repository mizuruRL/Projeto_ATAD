#pragma once
#include "date.h"

typedef struct patient{
    long int id;
    char sex[6]; // {“male”, “female”}
    int birthYear;
    char country[40]; //birth country
    char region[40];
    char infectionReason[100];
    long int infectedBy; // id of the infected patient
    Date confirmedDate;
    Date releasedDate;
    Date deceasedDate;
    char status[10]; // {“isolated, “released”, “deceased”}
} Patient;

typedef struct patient *PtPatient;

Patient createPatient(long int id, char *sex, int birthYear, char* country, char* region, char* infectionReason, long int infectedBy, Date confirmedDate, Date releasedDate, Date deceasedDate, char* status);
void printPatient(Patient p);
int getAge(Patient p);
int getNumberOfInfectedDays(Patient p);
int stringIsBlank(char *str);