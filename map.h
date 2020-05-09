#pragma once

#define MAP_OK            0
#define MAP_NULL          1
#define MAP_NO_MEMORY     2
#define MAP_EMPTY         3
#define MAP_FULL          4
#define MAP_UNKNOWN_KEY	  5

#pragma once

#include <stdbool.h>

typedef int MapKey;

typedef int MapValue;


#include <stdbool.h>

struct mapImpl;

typedef struct mapImpl *PtMap;

PtMap mapCreate(unsigned int initialCapacity);

int mapDestroy(PtMap *ptMap);

int mapPut(PtMap map, MapKey key, MapValue value);

int mapRemove(PtMap map, MapKey key, MapValue *ptValue);

int mapGet(PtMap map, MapKey key, MapValue *ptValue);


bool mapContains(PtMap map, MapKey key);

MapKey* mapKeys(PtMap map);

MapValue* mapValues(PtMap map);

int mapSize(PtMap map, int *ptSize);

bool mapIsEmpty(PtMap map);

int mapClear(PtMap map);

void mapPrint(PtMap map);

