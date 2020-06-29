#include <time.h>

typedef struct date {
    unsigned int day, month, year;
} Date;

Date createDate(int day, int month, int year);
void printDate(Date date);
Date stringToDate(char *str);
time_t dateToTimeT(Date date);
int getDayDifference(time_t dateEnd, time_t dateStart);