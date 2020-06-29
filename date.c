#include <stdio.h>
#include <stdlib.h>
#include "date.h"


Date createDate(int day, int month, int year){
    Date date;
    if(day > 31) day == 1;
    if(month > 12) month == 1;
    date.day = day;
    date.month = month;
    date.year = year;
    return date;
}

void printDate(Date date){
    printf("%d/%d/%d",date.day,date.month,date.year);
}

time_t dateToTimeT(Date date){ 
    time_t now = time(NULL);
    struct tm d1 = *localtime(&now);

    d1.tm_year = date.year;
    d1.tm_mon = date.month;
    d1.tm_mday = date.day;

    time_t dateT = mktime(&d1);
    
    return dateT;
}

int getDayDifference(time_t dateEnd, time_t dateStart) {
    double difference = difftime(dateEnd, dateStart);
    difference = difference/86400;
    return (int)difference;
}