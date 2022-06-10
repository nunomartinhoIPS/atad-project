#pragma once
#include "time.h"
#include "list.h"

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



void flightPrint(Flight f);
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

/**
 * @brief Shows all flight that have the passed airport has origin
 * 
 * @param flights [ in ] list of flights
 * @param airport [ in ] airport iata
 */
void showF(PtList flights, char airport[4]);