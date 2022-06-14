#pragma once

#define LOADER_OK                       0
#define LOADER_FILE_NOT_FOUND           1
#define LOADER_FILE_INCONSISTENCY       2
#define LOADER_ARRAY_ISSUE              3
#define LOADER_LIST_ISSUE               4
#define LOADER_MAP_ISSUE                5
#define LOADER_FLIGHT_CREATION_ISSUE    6



#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "airline.h"
#include "airport.h"
#include "list.h"
#include <float.h>
#include "utils.h"
#include "map.h"
#include "time.h"
#include <ctype.h>

int sizeOfLoadAR(int * size);

int loadAR(PtAirline * airlines, int size);

int loadAP(PtMap airports);

int loadF(PtList flights);
