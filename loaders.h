#pragma once

#define LOADER_OK                   0
#define LOADER_FILE_NOT_FOUND       1
#define LOADER_ARRAY_ISSUE          2
#define LOADER_LIST_ISSUE           3
#define LOADER_FILE_INCONSISTENCY   4
#define LOADER_MAP_ISSUE           5


#include "airline.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "map.h"

int sizeOfLoadAR(int * size);

int loadAR(PtAirline * airlines, int size);

int loadAP(PtMap airports);
