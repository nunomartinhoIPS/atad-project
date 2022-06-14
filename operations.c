#include "operations.h"

void printFlightsMenu(){
    system("cls"); // clear console.
    printf("\n===================================================================================");
    printf("\n\t\t\t\t\t\t\t\tALL FLIGHTS");
    printf("\n===================================================================================");
}

void listAP(PtMap airports, PtList flights){
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

void listAR(PtAirline airlines[], int aSize, PtList flights){
    int fSize;
    Flight f;
    listSize(flights, &fSize);
    for (int i = 0; i < aSize; i++){
        for (int j = 0; j < fSize; j++){
            listGet(flights, j, &f);
            if (equalsStringIgnoreCase(f.airline, airlines[i]->iatacode)){
                printf("\t");
                airlinePrint(airlines[i]);
                break;
            }
        }
    }
}

void showF(PtList flights, char* airport){
    int count = 0;
    int size;
    listSize(flights, &size);
        for(int i = 0; i<size; i++){
        Flight f;
        listGet(flights, i, &f);
        if(equalsStringIgnoreCase(f.originAirport, airport)){
            count++;
            flightPrint(&f);
        }
        }
        if (count == 0){
            printf("\n\n\t\t\t\t\t--Flight data not available for %s--\n", airport);
        }
}

void showAllPaged(PtList list){

    String command;
    int page = 0;
    int exit = 0;
    Flight flight;
    while (!exit)
    {
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

void showAllSample(PtList list){
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

void clearAll(PtAirline *airlines, PtMap ptAirports, PtList ptFlights, int sizeAirlines){

    for (int i = 0; i < sizeAirlines; i++)
    {
        free(airlines[i]);
    }

    mapDestroy(&ptAirports);
    listDestroy(&ptFlights);
}

void oLoadAR(PtAirline *airlines, int sizeAirlines) {
    int errorCode = loadAR(airlines, sizeAirlines);
    if (errorCode == LOADER_OK)
        printf("<%d> airline records imported\n", sizeAirlines);
    if (errorCode == LOADER_FILE_NOT_FOUND)
        printf("File not found\n");
}

void oLoadAP(PtMap airports){
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

/**
 * @brief sorts a list of flights by descending delay, if delay is the same sorts by flight number
 * 
 * @param flights [in] list of flights
 */
PtList sortByDelay(PtList flights){
    int size = 0;
    listSize(flights, &size);
    Flight f1;
    Flight f2;

    for(int i = 0; i<size-1; i++){
        int indexMin = i;
        for(int j = i; j<size-1; j++){
            listGet(flights, j, &f1);
            listGet(flights, indexMin, &f2);
            if(timeDiffSpecial(f1.scheduledArrival, f1.arrivalTime) == timeDiffSpecial(f2.scheduledArrival, f2.arrivalTime)){
                if(f1.flightNumber < f2.flightNumber){ 
                    indexMin = j;
                }
            }
            if(timeDiffSpecial(f1.scheduledArrival, f1.arrivalTime)>timeDiffSpecial(f2.scheduledArrival, f2.arrivalTime)){ 
                indexMin = j; 
            }
        }
        Flight fAux;
        Flight fAux2;

        listGet(flights, i, &fAux);
        listGet(flights, indexMin, &fAux2);

        listSet(flights, i, fAux2, &fAux2);
        listSet(flights, indexMin, fAux, &fAux);
    }
    return flights;
}

void topN(PtList flights, int n){
    PtList flightsCopy = listCreate();
    int size = 0;
    listSize(flights, &size);
    Flight aux;
    for(int i = 0; i < size; i++){
        listGet(flights, i, &aux);
        listAdd(flightsCopy, i, aux);
    }
    flightsCopy = sortByDelay(flightsCopy);
    for(int i = 0; i < n; i++){
        listGet(flightsCopy, i, &aux);
        PtFlight PtAux = &aux;
        flightPrint(PtAux);
    }
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
