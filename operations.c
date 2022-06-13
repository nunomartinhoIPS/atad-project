#include "operations.h"

void printFlightsMenu()
{
    printf("\n===================================================================================");
    printf("\n                          ALL FLIGHTS");
    printf("\n===================================================================================");
}

void listAP(PtMap airports, PtList flights)
{
    int aSize;
    int fSize;
    Flight f;
    mapSize(airports, &aSize);
    listSize(flights, &fSize);
    MapValue *values = mapValues(airports);
    for (int i = 0; i < aSize; i++)
    {
        for (int j = 0; j < fSize; j++)
        {
            listGet(flights, j, &f);
            if (f.destinationAirport == values[i].iataCode || f.originAirport == values[i].iataCode)
            {
                mapValuePrint(values[i]);
                break;
            }
        }
    }
}

void listAR(PtAirline airlines[], PtList flights)
{
    int aSize = sizeof(*airlines) / sizeof(*airlines[0]);
    int fSize;
    Flight f;
    listSize(flights, &fSize);
    for (int i = 0; i < aSize; i++)
    {
        for (int j = 0; j < fSize; j++)
        {
            listGet(flights, j, &f);
            if (f.airline == airlines[i]->iatacode)
            {
                airlinePrint(airlines[i]);
                break;
            }
        }
    }
}

void showF(PtList flights, char airport[4]) {
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
    if (count == 0)
    {
        printf("Flight data not available for %s.", airport);
    }
}

void showAllPaged(PtList list) {

    String command;
    int page = 0;
    int exit = 0;
    Flight flight;
    while (!exit) {
        system("clear"); // clear console.
        printFlightsMenu();
        printf("\nCommands  (NEXT, PREV, EXIT)");

        /*
         * Starts the index in the previous element (page = 0 * 20 = 0 starts in 0 element, page = 1 * 20 starts in the element 20)
         * To show only 20 pages, we do: page (0) + 1 * 20 = 20 pages in page 0, page (1) + 1 * 20 = 40 starts in the element 20 to element 40 (more 20 pages).
         */
        for (int i = page * 20; i < (page + 1) * 20; i++)
        {
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
        // problema e se chegar na ultima pagina?
        if (equalsStringIgnoreCase(command, "NEXT"))
        {
            page++;
        }

        if (equalsStringIgnoreCase(command, "PREV"))
        {
            if (page > 0)
                page--;
        }

        if (equalsStringIgnoreCase(command, "EXIT"))
        {
            exit = 1;
        }
    }
}

void showAllSample(PtList list) {
    printFlightsMenu();
    int size;
    listSize(list, &size);
    Flight flight;
    for (int i = 0; i < 100; i++)
    {
        int number = (rand() % ((size - 1) - 0 + 1)) + 0;
        listGet(list, number, &flight);
        listElemPrint(flight);
    }
}

int clearMemory(PtAirline *airlines, PtMap* ptAirports, PtList* ptFlights, int sizeAirlines) {
    
    PtMap curMap = *ptAirports;
    PtList curList = *ptFlights;
    
    if (airlines[0] == NULL) return ARRAY_NULL;
    if (curMap == NULL) return MAP_NULL;
    if (curList == NULL) return LIST_NULL;

    int sizeAirports, sizeFlights;
    
    for (int i = 0; i < sizeAirlines; i++) {
        free(airlines[i]);
    }
    airlines = NULL;
    printf("\n<%d> records deleted from Airlines\n", sizeAirlines);
    
    mapSize(curMap, &sizeAirports);
    mapDestroy(&curMap);   
    *ptAirports = NULL;
    printf("\n<%d> records deleted from Airports\n", sizeAirports);

    listSize(curList, &sizeFlights);
    listDestroy(&curList); 
    *ptFlights = NULL;
    printf("\n<%d> records deleted from Flights\n", sizeFlights);

    return OPERATION_OK;
    
}

void oLoadAR(PtAirline *airlines, int sizeAirlines) {
    int errorCode = loadAR(airlines, sizeAirlines);
    if (errorCode == LOADER_OK)
        printf("<%d> airline records imported\n", sizeAirlines);
    if (errorCode == LOADER_FILE_NOT_FOUND)
        printf("File not found\n");
}

void oLoadAP(PtMap airports)
{
    int sizeAirports;
    int errorCode = loadAP(airports);
    int mapErrorcode = mapSize(airports, &sizeAirports);
    if (mapErrorcode != MAP_OK)
    {
        printf("Something went wrong with the Map of StringCode to Airports, error: %d\n", mapErrorcode);
        return;
    }
    if (errorCode == LOADER_OK)
        printf("<%d> airport records imported\n", sizeAirports);
    if (errorCode == LOADER_FILE_NOT_FOUND)
        printf("File not found\n");
}

void oLoadF(PtList flights){
    int size, errorCode = loadF(flights), listErrorCode = listSize(flights, &size);
    if(listErrorCode != LIST_OK){
        printf("Something went wrong with the list of flights, error: %d\n", listErrorCode);
        return;
    }
    if(errorCode == LOADER_OK)
        printf("<%d> flight records imported\n", size);
    if(errorCode == LOADER_FILE_NOT_FOUND)
        printf("File not found\n");
}
