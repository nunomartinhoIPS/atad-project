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