#include "operations.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mapElem.h"
#include "stringCode.h"

void listAP(PtMap airports, PtList flights){
    int aSize=0;
    int fSize=0;
    Flight f;
    mapSize(airports, &aSize);
    listSize(flights, &fSize);
    MapValue* values = mapValues(airports);
    for(int i = 0; i < aSize; i++){
        for(int j = 0; j<fSize; j++){
            listGet(flights, j, &f);
            if(f.destinationAirport==values[i].iataCode || f.originAirport==values[i].iataCode){
                mapValuePrint(values[i]);
                break;
            }
        }
    }
}

void listAR(PtAirline airlines[], PtList flights){
    int aSize=0;
    int fSize=0;
    Flight f;
    listSize(airlines, &aSize);
    listSize(flights, &fSize);
    for(int i = 0; i < aSize; i++){
        for(int j = 0; j<fSize; j++){
            listGet(flights, j, &f);
            if(f.airline==airlines[i]->iatacode){
                airlinePrint(airlines[i]);
                break;
            }
        }
    }
}