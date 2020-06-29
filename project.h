#include "utils.h"

void menu();

void commandLoadP(PtList *patients);

void commandLoadR(PtMap *regions);

void commandClear(PtList patients, PtMap regions);

int commandQuit(PtList *patients, PtMap *regions);

void commandAverage(PtList list);

void commandFollow(PtList list, long int id);

void commandSex(PtList list);

void commandShow(PtList list, long int id);

void commandTop5(PtList list);

void commandOldest(PtList list);

void commandGrowth();

void commandMatrix();

void commandRegions();

void commandReport();