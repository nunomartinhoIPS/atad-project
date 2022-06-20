/**
 * @file airline.h
 * @brief Defines the types Airline and PtAirline
 * 
 * Defines the type Airline, PtAirline and associated operations.
 * 
 */
#pragma once

#define ARRAY_NULL			1

typedef struct airline {
    char iatacode[3];
    char name[100];
} Airline;

typedef Airline *PtAirline;

/**
 * @brief Creates an airline
 * 
 * @param iatacode  [in] String iatacode of the airline
 * @param name      [in] String name of the airline
 * @return PtAirline created
 */
PtAirline airlineCreate(char* iatacode, char* name);

/**
 * @brief Prints an airline
 * 
 * @param a [in] airline to print.
 */
void airlinePrint(PtAirline a);
