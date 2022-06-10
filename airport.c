#include "airport.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

PtAirport airportCreate(char * iata, char * name, char * city, char * state, 
                        float latitude, float longitude, int timezone){
    PtAirport a = (PtAirport) malloc(sizeof(Airport));
    if(a == NULL) return NULL;
    strcpy(a->iataCode, iata);
    strcpy(a->airport, name);
    strcpy(a->city, city);
    strcpy(a->state, state);
    a->latitude = latitude;
    a->longitude = longitude;
    a->timeZone = timezone;
    return a;
}

int airportPrint(PtAirport a){
    if (a == NULL) return AIRPORT_NULL;
    printf("Airport:\n\tIATA: %s, name: %s in %s, %s\n\t lat: %f, long: %f, timezone: %d",
        a->iataCode, a->airport, a->city, a->state, a->latitude, a->longitude, a->timeZone);
    return AIRPORT_OK;
}