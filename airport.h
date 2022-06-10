#pragma once


typedef struct airport {
    char iataCode[4];
    char airport[100];
    char city[35];
    char state[3];
    float latitude;
    float longitude;
    int timeZone;
} Airport;

typedef Airport * PtAirport;

#define AIRPORT_OK      0
#define AIRPORT_NULL    1

PtAirport airportCreate(char * iata, char * name, char * city, char * state, float latitude, float longitude, int timezone);

int airportPrint(PtAirport a);
