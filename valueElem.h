#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "region.h"

typedef int MapKey;

typedef Region MapValue;

#include "map.h"

typedef struct keyValue {
	MapKey key;
	MapValue value;
} KeyValue;

typedef struct mapImpl {
	KeyValue *elements;
	int capacity;
	int size;
} MapImpl;

void mapKeyPrint(MapKey key);

void mapValuePrint(MapValue value);

bool mapKeyEquals(MapKey key1, MapKey key2);