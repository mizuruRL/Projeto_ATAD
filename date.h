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
 * @file date.h
 * @author André Dias, Tomás Barroso
 * @brief Defines the data type Date and corresponding functions
 * @version 0.1
 * @date 2020-06-30
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <time.h>

typedef struct date {
    unsigned int day, month, year;
} Date;

/**
 * @brief Create a Date object
 * 
 * @param day Day (if bigger than 31, then it defaults to 1)
 * @param month Month (if bigger than 12, then it defaults to 1)
 * @param year Year
 * @return Date Date object
 */
Date createDate(int day, int month, int year);

/**
 * @brief Prints a given Date object
 * 
 * @param date 
 */
void printDate(Date date);

/**
 * @brief Converts a string to a Date object
 * 
 * @param str String with date
 * @return Date Date object (0/0/0 date if string is empty)
 */
Date stringToDate(char *str);

/**
 * @brief Converts a date object into time_t. Used to get differences between dates.
 * 
 * @param date Date object to convert
 * @return time_t Date in time_t
 */
time_t dateToTimeT(Date date);

/**
 * @brief Get the difference in days between two dates in time_t (dateEnd - dateStart)
 * 
 * @param dateEnd Earliest date in time_t
 * @param dateStart Oldest date in time_t
 * @return double Day difference in double
 */
double getDayDifference(time_t dateEnd, time_t dateStart);

/**
 * @brief Checks if the date is unknown (0/0/0)
 * 
 * @param date Date object to check
 * @return int 1 if unknown, 0 if otherwise
 */
int dateUnknown(Date date);