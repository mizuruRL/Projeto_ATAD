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
 * @file patient.h
 * @author André Dias, Tomás Barroso
 * @brief Defines the Patient data type and corresponding functions
 * @version 0.1
 * @date 2020-06-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
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

/**
 * @brief Create a Patient object, if string parameters are blank, they are then initialized as empty. Date parameters that dont comply get defaut values.
 * 
 * @param id Long integer ID
 * @param sex String with sex
 * @param birthYear Integer with birth year
 * @param country String with country name
 * @param region String with region name
 * @param infectionReason String with infection reason
 * @param infectedBy Long integer ID of patient who infected this patient
 * @param confirmedDate Date type with confirmed date
 * @param releasedDate Date type with released date
 * @param deceasedDate Date type with deceased date
 * @param status String with current patient status
 * @return Patient Created patient
 */
Patient createPatient(long int id, char *sex, int birthYear, char* country, char* region, char* infectionReason, long int infectedBy, Date confirmedDate, Date releasedDate, Date deceasedDate, char* status);

/**
 * @brief Prints the given patient object
 * 
 * @param p Patient to print
 */
void printPatient(Patient p);

/**
 * @brief Get the Age of given patient object
 * 
 * @param p Patient object to get age
 * @return int Age
 */
int getAge(Patient p);

/**
 * @brief Get the Number Of Infected Days from given patient object in double format (Operations between dates are done using difftime)
 * 
 * @param p Patient object to get Number of Infected Days
 * @return double Difference of days 
 */
double getNumberOfInfectedDays(Patient p);

/**
 * @brief Checks if a given string is blank
 * 
 * @param str String to check
 * @return int 1 if blank, 0 if otherwise
 */
int stringIsBlank(char *str);

/**
 * @brief Get the Status of a given patient object
 * 
 * @param p Patient object
 * @return char 'i' : isolated; 'd' : deceased; 'r' : released; 'u' : unknown
 */
char getStatus(Patient p);