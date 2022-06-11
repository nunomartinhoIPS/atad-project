#pragma once

#include "time.h"
#include "list.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stringCode.h"

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

typedef Flight * PtFlight;
/**
 * @brief Shows all flights in a paged form.
 * 
 * @param list [ in ] list of flights
 */
void showAllPaged(PtList list);

/**
 * @brief Shows 100 random flights.
 * 
 * @param list [ in ] list of flights
 */
void showAllSample(PtList list);

void printFlightsMenu();
