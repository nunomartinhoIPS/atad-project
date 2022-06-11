#include "airline.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

PtAirline airlineCreate(char * iatacode, char * name){
    PtAirline a = (PtAirline) malloc(sizeof(Airline));
    if(a == NULL) return NULL;
    strcpy(a->iatacode, iatacode);
    strcpy(a->name, name);
    return a;
}

void airlinePrint(PtAirline a){
    printf("%s ,  %s\n", a->name, a->iatacode);
}