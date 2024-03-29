/**
 * @file operations.h
 *
 * @brief Definition of the Operations methods in C
 * 
 * Provides the operations needed for this project
 * 
 */
#pragma once

#include "airport.h"
#include "flight.h"
#include "airline.h"
#include "time.h"
#include "map.h"
#include "list.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mapElem.h"
#include "stringCode.h"
#include "utils.h"
#include "loaders.h"
#include "input.h"

/**
 * @brief loads arlines
 * 
 * @param airlines      [in] array of airlines
 * @param sizeAirlines  [in] size of array
 */
void oLoadAR(PtAirline *airlines, int sizeAirlines);

/**
 * @brief loads airports
 * 
 * @param airports  [in] map of all airports
 */
void oLoadAP(PtMap airports);

/**
 * @brief loads flights
 * 
 * @param flights  [in] list of all flights
 */
void oLoadF(PtList flights, PtMap airports);

/**
 * @brief Shows all airports with flights
 * 
 * @param airports  [in] map of all airports
 * @param flights   [in] list of all fligts
 */
void listAP(PtMap airports, PtList flights);

/**
 * @brief Shows all airlines with flights
 * 
 * @param airlines  [in] array of airlines
 * @param aSize     [in] size of the array
 * @param flights   [in] list of all flights
 */
void listAR(PtAirline airlines[], int aSize, PtList flights);
/**
 * @brief shows menu for the paginated form or for the sample
 * 
 * @param list [in] list of flights
 */
void showAll(PtList list);

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
 * @param flights [in] list of flights
 * @param airport [in] airport iata
 */
void showF(PtList flights, char airport[4]);

/**
 * @brief Free all resources of map, list and array
 * 
 * @param airlines      [in] array
 * @param airports      [in] ADDRESS OF pointer to the map
 * @param flights       [in] ADDRESS OF pointer to the list
 * @param sizeAirlines  [in] size of array
 */
void clearMemory(PtAirline* airlines , PtMap *ptAirports, PtList *ptFlights, int sizeAirlines);

/**
 * @brief shows N flight sorted by descending delay
 * 
 * @param flights [in] list of all flights
 * @param n [in] number of flights to show
 */
void topN(PtList flights, int n);

/**
 * @brief Method to show from each airline ne number of flights that departed
 * and arrived at the scheduled time.
 * 
 * @param airlines      [in]    pointer to the array of airlines 
 * @param sizeAirlines  [in]    size of airlines array
 * @param flights       [in]    pointer to the list of flights
 */
void onTime(PtAirline * airlines, int sizeAirlines, PtList flights);

/**
 * @brief Shows data from airports ordered by:
 *  - city      ASC
 *  - city      DESC
 *  - Latitude  DESC
 *  - Longitude ASC
 * 
 * @param airports  [in]    map of airports
 */
void airport_s(PtMap airports);

/**
 * @brief Method to show how many flights, departure delays and average 
 * departure delays of flights departed from each airport
 * 
 * @param airports  [in]    pointer to the map of airports
 * @param flights   [in]    pointer to the list of flights
 */
void funcAirports(PtMap airports, PtList flights);
/**
 * @brief shows all airports that each flight passes through
 * 
 * @param airlines      [in]    array of airlines
 * @param flights       [in]    pointer to the list of flights
 * @param sizeAirlines  [in]    size of airlines array
 */
void showAP(PtAirline *airlines, PtList flights, int sizeAirlines);
/**
 * @brief calculates the average of all flight distances.
 * 
 * @param airport      [in]     String of the iatacode
 * @param flights      [in]    pointer to the list of flights
 */
void Average(PtList flights, String airport);
