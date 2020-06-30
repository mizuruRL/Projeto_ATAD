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
 * @file utils.h
 * @author André Dias, Tomás Barroso
 * @brief Defines auxiliary functions to be implemented
 * @version 0.1
 * @date 2020-06-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "list.h"
#include "map.h"
#include <math.h>

/**
 * @brief Auxiliary function that returns if two strings are equal, ignoring case
 * 
 * @param str1 String to compare
 * @param str2 String to compare
 * @return int Result of comparison (Refer to strcmp)
 */
int equalsStringIgnoreCase(char str1[], char str2[]);

/**
 * @brief Auxiliary function that splits a string into tokens
 * 
 * @param string String to split
 * @param nFields Number of wanted tokens
 * @param delim Delimiter character
 * @return char** Array of strings with respective tokens
 */
char** split(char *string, int nFields, const char *delim);

/**
 * @brief Auxiliary function that imports the patients from a file onto a given list
 * 
 * @param filename File path to file
 * @param patients List to import to
 */
void importPatientsFromFile(char *filename, PtList *patients);

/**
 * @brief Auxiliary function that imports the regions from a file onto a given map
 * 
 * @param filename File path to file
 * @param regions Map to import to
 */
void importRegionsFromFile(char *filename, PtMap *regions);

/**
 * @brief Auxiliary function that transforms a string to a date
 * 
 * @param str String to convert
 * @return Date Result of conversion (RETURNS 0/0/0 IF BLANK STRING)
 */
Date stringToDate(char *str);

/**
 * @brief Auxiliary function that transforms a string seperated by commas into a float value using pointer arithmetic
 * 
 * @param str String to transform (with commas)
 * @return float Final result without commas
 */
float stringToNumber(char *str);

/**
 * @brief Auxiliary function that gets a patient by its id, in a given list
 * 
 * @param list [IN] List to search
 * @param id [IN] ID to search
 * @param ptElem [OUT] Address to store the result
 * @return int LIST_NULL, LIST_EMPTY, LIST_LIST_OK, LIST_INVALID_RANK (Values defined in list.h)
 */
int listGetById(PtList list, long int id, ListElem *ptElem);

/**
 * @brief Auxiliary function that prints the top N (user choice) released patients.
 * 
 * @param list Patient list
 * @param n Number of ranks to print
 * @param listSize Size of the list
 */
void printTopNReleased(PtList list, int n, int listSize);

/**
 * @brief Auxiliary function to check if a given rank is already in the array (for printTopNReleased)
 * 
 * @param rank Rank to check
 * @param arr Array to check in
 * @param size Size of the array to check
 * @return int 1 if ignored, 0 if otherwise
 */
int isRankIgnored(int rank, int *arr, int size);

/**
 * @brief Get the Oldest Age By Sex object
 * 
 * @param list Patient list
 * @param sex String with sex to check
 * @param listSize Patient list size
 * @return int Maximum age of given sex
 */
int getOldestAgeBySex(PtList list, char *sex, int listSize);

/**
 * @brief Prints status stats by given age bracket
 * 
 * @param list Patients list
 * @param listSize Patients list size
 * @param lowerlim Minimum age of interval (inclusive)
 * @param upperlim Maximum age of interval (inclusive)
 */
void showStatusStatsByAge(PtList list, int listSize, int lowerlim, int upperlim);

/**
 * @brief Shows infection rate and mortality rate growth between given date and a day before given date
 * 
 * @param list 
 * @param date 
 * @param listSize 
 */
void showGrowth(PtList list, Date date, int listSize);

/**
 * @brief Get the growth rate ((val1 - val2)/val2)
 * 
 * @param val1 Present value
 * @param val2 Past value
 * @return double Result of rate, unrounded
 */
double getRate(double val1, double val2);

/**
 * @brief Get the Average result (val1/val2)
 * 
 * @param val1 Top value
 * @param val2 Bottom value
 * @return double Result of average, unrounded
 */
double getAverage(double val1, double val2);

/**
 * @brief Auxiliary function that sorts a given array of strings using bubble sort
 * 
 * @param strings Array with strings to sort
 * @param size Size of array
 */
void orderStringArrAlphaBBsort(char* strings[], int size);

/**
 * @brief Auxiliary function that checks if a given string is inside array
 * 
 * @param strings Array of strings
 * @param size Size of array
 * @param string String to check
 * @return int 1 if repeated, 0 if otherwise
 */
int stringIsRepeated(char* strings[], int size, char* string);