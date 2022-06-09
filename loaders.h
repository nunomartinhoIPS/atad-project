#pragma once

#define LOADER_OK               0
#define LOADER_FILE_NOT_FOUND   1
#define LOADER_ARRAY_ISSUE      2


#include "airline.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int sizeOfLoadAR(int * size);

int LoadAR(PtAirline * airlines, int size);
