#include "airport.h"

Airport airportCreate(char * iata, char * name, char * city, char * state, float latitude, float longitude, int timezone){
    Airport a;
    strcpy(a.iataCode, iata);
    strcpy(a.airport, name);
    strcpy(a.city, city);
    strcpy(a.state, state);
    a.latitude = latitude;
    a.longitude = longitude;
    a.timeZone = timezone;
    return a;
}

void airportPrint(Airport a){
    printf("%-15s %-60s %-35s %-10s %-15f %-15f %-d\n",a.iataCode, a.airport, a.city, a.state, a.latitude, a.longitude, a.timeZone);
    //return AIRPORT_OK;
}
