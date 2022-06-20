/**
 * @file flight.h
 * @brief Defines the types Flight and PtFlight
 * 
 * Defines the type Flight, PtFlight and associated operations.
 * 
 */
#pragma once

#include "time.h"
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

typedef struct flight* PtFlight;
/**
 * @brief prints a flight
 * 
 * @param flight flight to print
 */
void flightPrint(PtFlight flight);
/**
 * @brief 
 * 
 * @param day                   [in] day of the flight
 * @param dayOfWeek             [in] dayOfWeek of the flight
 * @param airline               [in] airline of the flight
 * @param flightNumber          [in] originAirport of the flight   
 * @param originAirport         [in] destinationAirport of the flight    
 * @param destinationAirport    [in] destination of the flight
 * @param scheduledDeparture    [in] scheduledDeparture of the flight
 * @param departureTime         [in] departureTime of the flight
 * @param departureDelay        [in] departureDelay of the flight
 * @param scheduledTravelTime   [in] scheduledTravelTime of the flight
 * @param distance              [in] distance of the flight
 * @param scheduledArrival      [in] scheduledArrival of the flight
 * @param arrivalTime           [in] arrivalTime of the flight
 * @param arrivalDelay          [in] arrivalDelay of the flight
 * @return Flight created
 */
Flight flightCreate(int day, int dayOfWeek, char* airline, int flightNumber, char* originAirport, char* destinationAirport, 
Time scheduledDeparture, Time departureTime, int departureDelay, int scheduledTravelTime, int distance, Time scheduledArrival, Time arrivalTime, int arrivalDelay);
