typedef struct date {
    unsigned int day, month, year;
} Date;

Date createDate(int day, int month, int year);
void printDate(Date date);