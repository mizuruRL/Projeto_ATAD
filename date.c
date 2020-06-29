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
    struct tm d1;

    d1.tm_year = date.year;
    d1.tm_mon = date.month;
    d1.tm_mday = date.day;
    d1.tm_min = 0;
    d1.tm_sec = 0;
    d1.tm_hour = 0;
    d1.tm_zone = 0;
    d1.tm_gmtoff = 0;
    d1.tm_isdst = 0;
    d1.tm_zone = "gmt";

    time_t dateT = mktime(&d1);
    
    return dateT;
}

double getDayDifference(time_t dateEnd, time_t dateStart) {
    double difference = difftime(dateEnd, dateStart);
    difference = difference/86400;
    return difference - 1;
}

int dateUnknown(Date date) {
    if(date.day == 0 && date.month == 0 && date.year == 0) return 1;
    return 0;
}