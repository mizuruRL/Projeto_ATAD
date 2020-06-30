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
 * @file commandsImpl.h
 * @author André Dias, Tomás Barroso
 * @brief Definition of command functions to be implemented
 * @version 0.1
 * @date 2020-06-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "utils.h"

/**
 * @brief Simple method to show the main menu
 * 
 */
void menu();

/**
 * @brief Loads patients onto memory
 * 
 * @param patients Address of list of patients to load
 */
void commandLoadP(PtList *patients);

/**
 * @brief Loads regions onto memory
 * 
 * @param regions 
 */
void commandLoadR(PtMap *regions);

/**
 * @brief Clears regions and patients
 * 
 * @param patients Patients list to clear
 * @param regions Regions map to clear
 */
void commandClear(PtList patients, PtMap regions);

/**
 * @brief Quits the program and cleans memory leftovers
 * 
 * @param patients Patients list to free
 * @param regions Regions map to free
 * @return int 1 to exit the command interpreter inside main function
 */
int commandQuit(PtList *patients, PtMap *regions);

/**
 * @brief Shows the average age for every patient status
 * 
 * @param list Patients list
 */
void commandAverage(PtList list);

/**
 * @brief Follows a patient's contamination chain by given ID, if it exists
 * 
 * @param list Patients list
 * @param id Patient id
 */
void commandFollow(PtList list, long int id);

/**
 * @brief Shows the percentage of patients of every sex
 * 
 * @param list Patients list
 */
void commandSex(PtList list);

/**
 * @brief Shows a patient's data by given id
 * 
 * @param list Patients list
 * @param id Patient id
 */
void commandShow(PtList list, long int id);

/**
 * @brief Shows top 5 patients by number of infected days, in decreasing order
 * 
 * @param list Patients list
 */
void commandTop5(PtList list);

/**
 * @brief Shows the list of the oldest patients of each sex, according to their birth year
 * 
 * @param list Patients list
 */
void commandOldest(PtList list);

/**
 * @brief Shows the growth rate of the number of deaths and infections between a given date and the day before the given date
 * 
 * @param list Patients list
 * @param date String with date
 */
void commandGrowth(PtList list, char* date);

/**
 * @brief Shows a 6x3 matrix with total number of patients of each status, in age brackets
 * 
 * @param list Patients list
 */
void commandMatrix(PtList list);

/**
 * @brief Shows the list of regions in alphabetical order that still have active cases
 * 
 * @param list Patients list
 * @param map Regions map
 */
void commandRegions(PtList list, PtMap map);

/**
 * @brief Creates a report.txt in the files folder with mortality, incident rate, and lethality data and prints it on the screen
 * 
 * @param map Regions map
 * @param list Patients list
 */
void commandReport(PtMap map, PtList list);