#include <stdio.h>
#include <stdlib.h>
#include "date.h"


Date createDate(int day, int month, int year){
    Date date;
    if(day == 0 || day > 31) day == 1;
    if(month == 0 || month > 12) month == 1;
    date.day = day;
    date.month = month;
    date.year = year;
    return date;
}

void printDate(Date date){
    printf("%d/%d/%d",date.day,date.month,date.year);
}