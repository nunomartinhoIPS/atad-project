#include "loaders.h"
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

int sizeOfLoadAR(int * size){
    FILE* ptFile = fopen("./csv_data/airlines.csv", "r");
    if(ptFile == NULL) return LOADER_FILE_NOT_FOUND;
    char s[256];
    *size = 0;
    fgets(s, sizeof(s), ptFile);
    while(fgets(s, sizeof(s), ptFile) != NULL)
        *size+=1;
    fclose(ptFile);
    return LOADER_OK;
}

int loadAR(PtAirline* airlines, int size){
    if (airlines == NULL) return LOADER_ARRAY_ISSUE;
    FILE* ptFile;
    ptFile = fopen("./csv_data/airlines.csv", "r");
    if(ptFile == NULL) return LOADER_FILE_NOT_FOUND;
    char s[256];
    fgets(s, sizeof(s), ptFile); //skip first line bc its just header
    int line = 0;
    while(fgets(s, sizeof(s), ptFile) != NULL){
        char * iata = strtok(s, ";");
        char * name = strtok(NULL, ";");
        if(iata == NULL || name == NULL) return LOADER_FILE_INCONSISTENCY;
        name[strlen(name)-2] = '\0';
        airlines[line++] = airlineCreate(iata, name);
    }
    fclose(ptFile);
    return LOADER_OK;
}

int loadAP(PtMap airports){
    if (airports == NULL) return LOADER_MAP_ISSUE;
    FILE * ptFile = fopen("./csv_data/airports.csv", "r");
    if(ptFile == NULL) return LOADER_FILE_NOT_FOUND;
    char s[256];
    fgets(s, sizeof(s), ptFile);
    int line = 0;
    while(fgets(s, sizeof(s), ptFile)!= NULL){
        char * iata = strtok(s, ";");
        if(iata == NULL) return LOADER_FILE_INCONSISTENCY;
        char * name = strtok(NULL, ";");
        if(name == NULL) return LOADER_FILE_INCONSISTENCY;
        char * city = strtok(NULL, ";");
        if(city == NULL) return LOADER_FILE_INCONSISTENCY;
        char * state = strtok(NULL, ";");
        if(state == NULL) return LOADER_FILE_INCONSISTENCY;
        char * latitude = strtok(NULL, ";");
        if(latitude == NULL) return LOADER_FILE_INCONSISTENCY;
        char * longitude = strtok(NULL, ";");
        if(longitude == NULL) return LOADER_FILE_INCONSISTENCY;
        char * timezone = strtok(NULL, ";");
        replace(latitude, ',', '.');
        replace(longitude, ',', '.');
        Airport a = airportCreate(iata, name, city, state, atof(latitude), atof(longitude), atoi(timezone));
        StringCode s = stringCodeCreate(a.iataCode);
        if(mapPut(airports, s, a)!=MAP_OK) return LOADER_MAP_ISSUE;
    }
    fclose(ptFile);
    return LOADER_OK;
}

int loadF(PtList flights){
    if(flights == NULL) return LOADER_LIST_ISSUE;
    FILE * ptFile = fopen("./csv_data/flights.csv", "r");
    if(ptFile == NULL) return LOADER_FILE_NOT_FOUND;
    char s[256];
    fgets(s, sizeof(s), ptFile);
    int line = 0;
    while(fgets(s, sizeof(s), ptFile)!=NULL){
        char * day = strtok(s, ";");
        if(day == NULL) return LOADER_FILE_INCONSISTENCY;
        
        char * dayWeek = strtok(NULL, ";");
        if(dayWeek == NULL) return LOADER_FILE_INCONSISTENCY;
        
        
        char * airline = strtok(NULL, ";");
        if(airline == NULL) return LOADER_FILE_INCONSISTENCY;
        
        
        char * flightnum = strtok(NULL, ";");
        if(flightnum == NULL) return LOADER_FILE_INCONSISTENCY;
        
        
        char * origAirport = strtok(NULL, ";");
        if(origAirport == NULL) return LOADER_FILE_INCONSISTENCY;
        
        
        char * destAirport = strtok(NULL, ";");
        if(destAirport == NULL) return LOADER_FILE_INCONSISTENCY;
        
        
        char * schedDep = strtok(NULL, ";");
        if(schedDep == NULL) return LOADER_FILE_INCONSISTENCY;
        
        
        char * timeDep = strtok(NULL, ";");
        if(timeDep == NULL) return LOADER_FILE_INCONSISTENCY;
        
        
        char * dist = strtok(NULL, ";");
        if(dist == NULL) return LOADER_FILE_INCONSISTENCY;
        
        char * schedArr = strtok(NULL, ";");
        if(schedArr == NULL) return LOADER_FILE_INCONSISTENCY;
        
        
        char * timeArr = strtok(NULL, ";");
        if(timeArr == NULL) return LOADER_FILE_INCONSISTENCY;
        //@todo luis, tenho que fazer para valores que sao 30 ou 33 que e' meia noite e 30 e meia noite e 33
        printf("testing --------------- sched dep = %s\n", schedDep);
        char * hour, * min;
        hour = strncpy(hour, schedDep, 1);
        min = strncpy(hour, schedDep + 2, 3-2);
        printf("sched Dep: %s\t\t%s:%s\n", schedDep, hour, min);
    }
}
