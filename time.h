#pragma once

typedef struct time {
	int hour, min;
} Time;

Time timeCreate(int hour, int min);

int timeDiff(Time time1,Time time2);

int timeDiffSpecial(Time time1,Time time2);

void timePrint(Time t);
