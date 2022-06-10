#include "airport.h"
#include "list.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mapElem.h"
#include "stringCode.h"

void airportPrint(Airport a){
    printf(
        "\nIata Code: %s \nAirport: %s \nCity: %s \nState: %s \nLatitude: %.5f \nLongitude: %.5f \nTime Zone: %d", 
        a.iataCode, a.airport, a.city, a.state, a.latitude, a.longitude, a.timeZone
    );
}