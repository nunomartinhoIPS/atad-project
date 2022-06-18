#include "loaders.h"

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

int digitNum(char * s){
    int digitLen=0;
    for (int i = 0; i<strlen(s); i++)
        if(isdigit(s[i])) digitLen++;
    return digitLen;
}

void formatTime(char * from, char * toHour, char * toMin){
    /**
     * im really not proud of this method but there was no other way to do it, i really tried big braining it
     */
    
    int numOfDigits = digitNum(from);

    if(numOfDigits == 1){
        char s [3]= "0";
        s[1] = from[0];
        s[2] = '\0';
        strcpy(toMin, s);
        strcpy(toHour, "00");
        return;
    }
    
    if(numOfDigits == 2) {
        strcpy(toMin, from);
        strcpy(toHour, "00");
        return;
    }
    
    if(numOfDigits == 3){
        strncpy(toHour, from, 1);
        toHour[1] = '\0';
        strncpy(toMin, from + 1, 2);
        toMin[2] = '\0';
        return;
    }
    
    if(numOfDigits == 4){
        strncpy(toHour, from, 2);
        toHour[2] = '\0';
        strncpy(toMin, from + 2, 2);
        toMin[2] = '\0';
    }

}

static int getTimezone(PtMap airports, char* iata){
    Airport a;
    if(mapGet(airports, stringCodeCreate(iata), &a)!=MAP_OK) return -999;
    return a.timeZone;
}

int loadF(PtList flights, PtMap airports){
    if(flights == NULL) return LOADER_LIST_ISSUE;
    if(airports == NULL) return LOADER_MAP_ISSUE;
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
        

        char hour[3], min[3];


        formatTime(schedDep, hour, min);
        Time tschedDep = timeCreate(atoi(hour), atoi(min));
        
        formatTime(timeDep, hour, min);
        Time ttimeDep = timeCreate(atoi(hour), atoi(min));
        
        formatTime(schedArr, hour, min);
        Time tschedArr = timeCreate(atoi(hour), atoi(min));

        formatTime(timeArr, hour, min);
        Time ttimeArr = timeCreate(atoi(hour), atoi(min));
        

        int depDelay = timeDiffSpecial(tschedDep, ttimeDep), 
            timezoneO = getTimezone(airports, origAirport), 
            timezoneD = getTimezone(airports, destAirport),
            schedTravTime = timeDiffSpecial(tschedDep, tschedArr)+((timezoneO-timezoneD)*60),
            arrDelay = timeDiffSpecial(tschedArr, ttimeArr);

        if(listAdd(flights, line, 
                flightCreate(atoi(day), atoi(dayWeek), airline, atoi(flightnum), origAirport, destAirport, tschedDep, ttimeDep, depDelay, schedTravTime, atoi(dist), tschedArr, ttimeArr, arrDelay))
                !=LIST_OK) 
                return LOADER_LIST_ISSUE;
        line++;
    }
    fclose(ptFile);
}
