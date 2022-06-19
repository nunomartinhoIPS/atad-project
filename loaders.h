#pragma once

#define LOADER_OK                       0
#define LOADER_FILE_NOT_FOUND           1
#define LOADER_FILE_INCONSISTENCY       2
#define LOADER_ARRAY_ISSUE              3
#define LOADER_LIST_ISSUE               4
#define LOADER_MAP_ISSUE                5
#define LOADER_FLIGHT_CREATION_ISSUE    6



#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "airline.h"
#include "airport.h"
#include "list.h"
#include <float.h>
#include "utils.h"
#include "map.h"
#include "time.h"
#include <ctype.h>


/**
 * @brief Method to determine the size of the array to be alocated for the Airlines
 * 
 * @param size      [out]   pointer to the int to put the value in
 * @return int error code if an error does occur, LOADER_OK if no error occurs
 */
int sizeOfLoadAR(int * size);

/**
 * @brief Method to load the Airlines from './csv_data/airlines.csv'
 * 
 * @param airlines  [out]   Pointer to the array in which to put the airlines loaded
 * @param size      [in]    size of the array
 * @return int error code if an error does occur, LOADER_OK if no error occurs
 */
int loadAR(PtAirline * airlines, int size);

/**
 * @brief Method to load the Airports from './csv_data/airports.csv'
 * 
 * @param airports  [out]   pointer to the map in which to put the airports loaded
 * @return int error code if an error does occur, LOADER_OK if no error occurs
 */
int loadAP(PtMap airports);

/**
 * @brief Method to load the Flights from './csv_data/flights.csv'
 * 
 * @param flights   [out]   pointer to the list in which to put the flights loaded 
 * @return int error code if an error does occur, LOADER_OK if no error occurs
 */
int loadF(PtList flights);
