#include "list.h"
#include "map.h"

int equalsStringIgnoreCase(char str1[], char str2[]);
char** split(char *string, int nFields, const char *delim);
void importPatientsFromFile(char *filename, PtList *patients);
void importRegionsFromFile(char *filename, PtMap *regions);
Date stringToDate(char *str);
float stringToNumber(char *str);
int listGetById(PtList list, long int id, ListElem *ptElem);
int getRanks(PtList list, int *ranks, int size, int listSize);
int isRankIgnored(int rank, int *arr, int size);
int getOldestAgeBySex(PtList list, char *sex, int listSize);