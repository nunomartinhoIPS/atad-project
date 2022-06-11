#pragma once
#include "time.h"

typedef struct flight {
    int day;
    int dayOfWeek;
    char airline[3];
    int flightNumber;
    char originAirport[4];
    char destinationAirport[4];
    Time scheduledDeparture;
    Time departureTime;
    int departureDelay;
    int scheduledTravelTime;
    int distance;
    Time scheduledArrival;
    Time arrivalTime;
    int arrivalDelay;
} Flight;

typedef Flight* PtFlight;

void flightPrint(PtFlight flight);

Flight flightCreate(int day, int dayOfWeek, char* airline, int flightNumber, char* originAirport, char* destinationAirport, 
Time scheduledDeparture, Time departureTime, int departureDelay, int scheduledTravelTime, int distance, Time scheduledArrival, Time arrivalTime, int arrivalDelay);
