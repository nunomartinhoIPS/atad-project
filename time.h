#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "input.h"

typedef struct time {
	int hour, min;
} Time;


Time timeCreate(int hour, int min);

int timeDiff(Time time1,Time time2);

int timeDiffSpecial(Time time1,Time time2);

void timePrint(Time t);
