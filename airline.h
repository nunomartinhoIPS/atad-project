#pragma once

#define ARRAY_NULL			1

typedef struct airline {
    char iatacode[3];
    char name[100];
} Airline;

typedef Airline *PtAirline;

//deve ser Airline e nao um ponteiro.
PtAirline airlineCreate(char* iatacode, char* name);

void airlinePrint(PtAirline a);
