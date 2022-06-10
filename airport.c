#include "airport.h"
#include "map.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mapElem.h"
#include "stringCode.h"

void airportPrint(Airport a){
    printf("\nIata Code: %s \nAirport: %s \nState: %s", a.iataCode, a.airport, a.state);
}
