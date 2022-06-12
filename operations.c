#include "operations.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mapElem.h"
#include "stringCode.h"
#include "utils.h"

void printFlightsMenu() {
    
        system("cls"); // clear console.
        printf("\n===================================================================================");
        printf("\n                          ALL FLIGHTS");
        printf("\n===================================================================================");
}

void listAP(PtMap airports, PtList flights){
    int aSize;
    int fSize;
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
    int aSize = sizeof(*airlines)/sizeof(*airlines[0]);
    int fSize;
    Flight f;
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


void showF(PtList flights, char airport[4]){
    int count = 0;
    int size;
    listSize(flights, &size);
    for(int i = 0; i<size; i++){
        Flight f;
        listGet(flights, i, &f);
        if(f.originAirport == airport){
            count++;
            flightPrint(&f);
        }
    }
    if(count==0){
        printf("Flight data not available for %s.", airport);
    }
}

void showAllPaged(PtList list) {

    String command;
    int page = 0;
    int exit = 0;
    Flight flight;
    while (!exit) {
        printFlightsMenu();
        printf("\nCommands  (NEXT, PREV, EXIT)");
        
        /* 
         * Starts the index in the previous element (page = 0 * 20 = 0 starts in 0 element, page = 1 * 20 starts in the element 20) 
         * To show only 20 pages, we do: page (0) + 1 * 20 = 20 pages in page 0, page (1) + 1 * 20 = 40 starts in the element 20 to element 40 (more 20 pages).
         */
        for (int i = page*20; i < (page+1)*20; i++) {
            listGet(list, i, &flight);
            listElemPrint(flight);
        }
        
        if (page > 0)
            printf("\n<------------PREV------------- PAGE [%d] ------------NEXT-------------> ", page);
        else
            printf("\n<------------EXIT------------- PAGE [%d] ------------NEXT-------------> ", page);
        
        printf("\ncommand> ");
        fgets(command, sizeof(command), stdin);
        command[strlen(command) - 1] = '\0';
        //problema e se chegar na ultima pagina?
        if (equalsStringIgnoreCase(command, "NEXT")){
            page++;
        }

        if (equalsStringIgnoreCase(command, "PREV")){
            if (page > 0) page--;
        }

        if (equalsStringIgnoreCase(command, "EXIT")){
            exit = 1;
        }

    }
}

void showAllSample(PtList list) {
    printFlightsMenu();
    int size;
    listSize(list, &size);
    Flight flight;
    for (int i = 0; i < 100; i++) {
        int number = (rand() % ((size-1) - 0 + 1)) + 0;
        listGet(list, number, &flight);
        listElemPrint(flight);
    }
}

void clearAll(PtAirline* airlines , PtMap ptAirports, PtList ptFlights, int sizeAirlines){

    for (int i = 0; i < sizeAirlines; i++) {
        free(airlines[i]);
    }

    mapDestroy(&ptAirports);
    listDestroy(&ptFlights);

}