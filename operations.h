#pragma once
#include "airport.h"
#include "flight.h"
#include "airline.h"
#include "map.h"
#include "list.h"

/**
 * @brief Shows all airports with flights
 * 
 * @param airports map of all airports
 * @param flights list of all fligts
 */
void listAP(PtMap airports, PtList flights);

/**
 * @brief Shows all airlines with flights
 * 
 * @param airlines array of airlines
 * @param flights list of all flights
 */
void listAR(PtAirline airlines[], PtList flights);

/**
 * @brief Shows all flights in a paged form.
 * 
 * @param list [in] list of flights
 */
void showAllPaged(PtList list);

/**
 * @brief Shows 100 random flights.
 * 
 * @param list [in] list of flights
 */
void showAllSample(PtList list);

/**
 * @brief Shows all flight that have the passed airport has origin
 * 
 * @param flights [ in ] list of flights
 * @param airport [ in ] airport iata
 */
void showF(PtList flights, char airport[4]);