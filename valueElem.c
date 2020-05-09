#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "valueElem.h"

int findIndexOfKey(PtMap map, MapKey key) {
	if (map == NULL) return -1;

	for (int i = 0; i < map->size; i++) {
		if (mapKeyEquals(map->elements[i].key, key)) {
			return i;
		}
	}
	return -1;
}

bool ensureCapacity(PtMap map) {
	if (map->size == map->capacity) {
		int newCapacity = map->capacity * 2;
		KeyValue* newArray = (KeyValue*) realloc( map->elements, 
									newCapacity * sizeof(KeyValue) );
		
		if(newArray == NULL) return false;

		map->elements = newArray;
		map->capacity = newCapacity;
	}
	
	return true;
}

PtMap mapCreate(unsigned int initialCapacity) {
	PtMap newMap = (PtMap)malloc(sizeof(MapImpl));
	if (newMap == NULL) return NULL;

	newMap->elements = (KeyValue*)calloc(initialCapacity, sizeof(KeyValue));
	if (newMap->elements == NULL) {
		free(newMap);
		return NULL;
	}

	newMap->size = 0;
	newMap->capacity = initialCapacity;

	return newMap;
}

int mapDestroy(PtMap *ptMap) {
	PtMap map = *ptMap;

	if (map == NULL) return MAP_NULL;

	free(map->elements);
	free(map);

	*ptMap = NULL;

	return MAP_OK;
}

int mapPut(PtMap map, MapKey key, MapValue value) {
	if (map == NULL) return MAP_NULL;

	int index = findIndexOfKey(map, key);
	if (index != -1) {
		map->elements[index].value = value;
		return MAP_OK;
	}
	else {
		if (!ensureCapacity(map)) return MAP_FULL;
		
		map->elements[map->size].key = key;
		map->elements[map->size].value = value;
		map->size++;

		return MAP_OK;
	}
}

int mapRemove(PtMap map, MapKey key, MapValue *ptValue) {
	if (map == NULL) return MAP_NULL;
	if (map->size == 0) return MAP_EMPTY;

	int index = findIndexOfKey(map, key);
	if (index == -1) return MAP_UNKNOWN_KEY;

	*ptValue = map->elements[index].value;
	map->elements[index] = map->elements[map->size - 1];
	map->size--;
	
	return MAP_OK;
}

int mapGet(PtMap map, MapKey key, MapValue *ptValue) {
	if (map == NULL) return MAP_NULL;
	if (map->size == 0) return MAP_EMPTY;

	int index = findIndexOfKey(map, key);
	if (index == -1) return MAP_UNKNOWN_KEY;

	*ptValue = map->elements[index].value;
	
	return MAP_OK;
}

bool mapContains(PtMap map, MapKey key) {
	if (map == NULL) return 0;

	return findIndexOfKey(map, key) != -1;
}

MapKey* mapKeys(PtMap map) {
	if (map == NULL || map->size == 0) return NULL;

	MapKey *keys = (MapKey*)calloc(map->size, sizeof(MapKey));

	for (int i = 0; i < map->size; i++) {
		keys[i] = map->elements[i].key;
	}

	return keys;
}

MapValue* mapValues(PtMap map) {
	if (map == NULL || map->size == 0) return NULL;

	MapValue *values = (MapValue*)calloc(map->size, sizeof(MapValue));

	for (int i = 0; i < map->size; i++) {
		values[i] = map->elements[i].value;
	}

	return values;
}

int mapSize(PtMap map, int *ptSize) {
	if (map == NULL) return MAP_NULL;
	*ptSize = map->size;
	return MAP_OK;
}

bool mapIsEmpty(PtMap map) {
	if (map == NULL) return 1;
	return (map->size == 0);
}

int mapClear(PtMap map) {
	if (map == NULL) return MAP_NULL;
	map->size = 0;
	return MAP_OK;
}

void mapPrint(PtMap map) {
	if (map == NULL) {
		printf("(MAP NULL)\n");
	}
	else if (mapIsEmpty(map)) {
		printf("(MAP EMPTY)\n");
	}
	else {
		for (int i = 0; i < map->size; i++) {
			mapKeyPrint(map->elements[i].key);
			printf(" : \n");
			mapValuePrint(map->elements[i].value);
		}
	}
}

void mapKeyPrint(MapKey key) {
	printf("%d \n", key);
}

void mapValuePrint(MapValue value) {
	printRegion(&value);
}

bool mapKeyEquals(MapKey key1, MapKey key2) {
	return (key1 == key2); 
}