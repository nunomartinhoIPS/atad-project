/**
 * @file airport.h
 * @brief Defines the types Airport
 * 
 * Defines the type Airport and associated operations.
 * 
 */
#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct airport {
    char iataCode[4];
    char airport[100];
    char city[35];
    char state[3];
    float latitude;
    float longitude;
    int timeZone;
} Airport;

#define AIRPORT_OK      0
#define AIRPORT_NULL    1
/**
 * @brief Creates an airport
 * 
 * @param iata      [in] iata of the airport
 * @param name      [in] name of the airport
 * @param city      [in] city of the airport
 * @param state     [in] state of the airport
 * @param latitude  [in] latitude of the airport
 * @param longitude [in] longitude of the airport
 * @param timezone  [in] timezone of the airport
 * @return Airport created
 */
Airport airportCreate(char * iata, char * name, char * city, char * state, float latitude, float longitude, int timezone);

/**
 * @brief prints an airport
 * 
 * @param a airport to print
 */
void airportPrint(Airport a);
