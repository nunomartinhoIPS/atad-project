#pragma once
#include "airport.h"
#include "flight.h"
#include "airline.h"
#include "map.h"
#include "list.h"

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
 * @param flights   [in] list of all flights
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
 * @param flights [in] list of flights
 * @param airport [in] airport iata
 */
void showF(PtList flights, char airport[4]);

void oLoadAR(PtAirline *airlines, int sizeAirlines);

void oLoadAP(PtMap airports);

void oLoadF(PtList flights);

/**
 * @brief Free all resources of map, list and array
 * 
 * @param airlines      [in] array
 * @param airports      [in] ADDRESS OF pointer to the map
 * @param flights       [in] ADDRESS OF pointer to the list
 * @param sizeAirlines  [in] size of array
 */
void clearAll(PtAirline* airlines , PtMap ptAirports, PtList ptFlights, int sizeAirlines);
