#include "list.h"
#include "listElem.h"
#include "map.h"
#include "mapElem.h"

int equalsStringIgnoreCase(char str1[], char str2[]);
char** split(char *string, int nFields, const char *delim);
void importPatientsFromFile(char *filename, PtList *patients);
void importRegionsFromFile(char *filename, PtMap *regions);
Date stringToDate(char *str);