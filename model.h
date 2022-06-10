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