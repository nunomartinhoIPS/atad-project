#include "loaders.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "airline.h"

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

int LoadAR(PtAirline * airlines, int size){
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
        name[strlen(name)-2] = '\0';
        airlines[line++] = airlineCreate(iata, name);
    }
    return LOADER_OK;
}