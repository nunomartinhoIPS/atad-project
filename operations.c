#include "operations.h"


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

void oLoadF(PtList flights, PtMap airports){
    if(airports == NULL){
        printf("Import airports first.\n");
        return;
    }
    int size, errorCode = loadF(flights, airports), listErrorCode = listSize(flights, &size);
    if(listErrorCode != LIST_OK){
        printf("Something went wrong with the list of flights, error: %d\n", listErrorCode);
        return;
    }
    if(errorCode == LOADER_OK)
        printf("<%d> flight records imported\n", size);
    if(errorCode == LOADER_FILE_NOT_FOUND)
        printf("File not found\n");
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
            if (equalsStringIgnoreCase(f.destinationAirport, values[i].iataCode) || equalsStringIgnoreCase(f.originAirport, values[i].iataCode))
            {
                printf("%s: %s %s %s\n", values[i].iataCode, values[i].airport, values[i].city, values[i].state);
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

void showAll(PtList list) {
    String command;
    int quit = 0;
    while (!quit){
        system("clear");
        printf("\n--SHOWALL MENU--\n<PAGES> Show all flights (paginated by 20)\n<RANDOM> Show 100 random flight data\n<BACK> Return Main Menu\n\n");
        printf("COMMAND>");
			
        fgets(command, sizeof(command), stdin);
		command[strlen(command) - 1] = '\0';

        if (equalsStringIgnoreCase(command, "PAGES")){
        		showAllPaged(list);
    	}
			
		if (equalsStringIgnoreCase(command, "RANDOM")){
        		showAllSample(list);
    	}
        
        if (equalsStringIgnoreCase(command, "BACK")){
        		quit = 1;
    	}

    }
}

void showAllPaged(PtList list) {
    String command;
    int page = 0;
    int exit = 0;
    Flight flight;
    while (!exit) {
        system("clear"); // clear console.
        /*
         * Starts the index in the previous element (page = 0 * 20 = 0 starts in 0 element, page = 1 * 20 starts in the element 20)
         * To show only 20 pages, we do: page (0) + 1 * 20 = 20 pages in page 0, page (1) + 1 * 20 = 40 starts in the element 20 to element 40 (more 20 pages).
         */
        printf("\n---------- FLIGHTS ---------- \n");
        printf("\nDay  Day of Week  Airline  Flight Number  Origin  Destination  Scheduled Departure  Departure Time  Scheduled Time  Distance  Scheduled Arrival  Arrival Time  Arrival Delay");
        for (int i = page * 20; i < (page + 1) * 20; i++)
        {
            listGet(list, i, &flight);
            listElemPrint(flight);
        }
        printf("\n\t\t\t\t<------------BACK------------- PAGE [%d] ------------NEXT-------------> ", page);


        printf("\ncommand> ");
        fgets(command, sizeof(command), stdin);
        command[strlen(command) - 1] = '\0';
        // problema e se chegar na ultima pagina?
        if (equalsStringIgnoreCase(command, "NEXT")) page++;

        if (equalsStringIgnoreCase(command, "BACK")) {
            if (page == 0) exit = 1;
            else if (page > 0) page--;
        }
    }
}

void showAllSample(PtList list){

    printf("\n---------- FLIGHTS ---------- \n");
    printf("\nDay  Day of Week  Airline  Flight Number  Origin  Destination  Scheduled Departure  Departure Time  Scheduled Time  Distance  Scheduled Arrival  Arrival Time  Arrival Delay");
    int size;
    listSize(list, &size);
    Flight flight;
    for (int i = 0; i < 100; i++) {
        int number = (rand() % ((size - 1) - 0 + 1)) + 0;
        listGet(list, number, &flight);
        listElemPrint(flight);
    }

    printf("\nPress enter to continue ...");
	getchar();
	system("clear");
}

void clearMemory(PtAirline *airlines, PtMap* ptAirports, PtList* ptFlights, int sizeAirlines) {
    
    PtMap curMap = *ptAirports;
    PtList curList = *ptFlights;

    if (airlines[0] != NULL) {
        for (int i = 0; i < sizeAirlines; i++) {
            free(airlines[i]);
        }
        memset( airlines, '\0', sizeof( airlines ) );
    }

    if (curMap != NULL && mapDestroy(&curMap) == MAP_OK) {
        *ptAirports = NULL;
    }
       
    if (curList != NULL && listDestroy(&curList) == LIST_OK) {
        *ptFlights = NULL;
    }

    
}

/**
 * @brief sorts a list of flights by descending delay, if delay is the same sorts by flight number
 * 
 * @param flights [in] list of flights
 */
static PtList sortByDelay(PtList flights){
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

void onTime(PtAirline * airlines, int sizeAirlines, PtList flights){
    int saidaHPrev [sizeAirlines], chegadaHPrev [sizeAirlines], sizeList, tolerancia;
    if(listSize(flights, &sizeList) != LIST_OK) return;
    Flight f;
    printf("\nItroduce a tolerance between 0 and 30 minutes:...");
    readInteger(&tolerancia);

    for(int i = 0 ; i<sizeAirlines; i++){
        saidaHPrev[i] = 0;
        chegadaHPrev[i] = 0;
    }

    for(int i = 0; i<sizeAirlines; i++){
        for(int j = 0; j<sizeList; j++){
            listGet(flights, j, &f);
            if(equalsStringIgnoreCase(f.airline, airlines[i]->iatacode)){
                if(f.arrivalDelay <= 0) chegadaHPrev[i] = chegadaHPrev[i] + 1;
                if(f.departureDelay <= 0) saidaHPrev[i] = saidaHPrev[i] + 1;
            }
        }
    }

    printf("\n\n%-15s %-15s %-15s\n", "Airline", "OT_Departures", "OT_Arrivals");
    for(int i = 0; i<sizeAirlines; i++){
        if(saidaHPrev[i] != 0 && chegadaHPrev!=0)
            printf("%-15s %-15d %-15d\n", airlines[i]->iatacode, saidaHPrev[i], chegadaHPrev[i]);
    }
}

static bool apcmp(Airport a, Airport b, int compVersion){
    if(compVersion == 1) return strcmp(a.city, b.city)<0;
    if(compVersion == 2) return strcmp(a.city, b.city)>0;
    if(compVersion == 3) return a.latitude<b.latitude;
    if(compVersion == 4) return a.longitude<b.longitude;
    return false;
}

void airport_s(PtMap airports){
    int size, cmp;
    if(mapSize(airports, &size)!=MAP_OK) return;

    printf("AIRPORT_S Menu\n");
    printf("1. Sort by City Ascending\n");
    printf("2. Sort by City Descending\n");
    printf("3. Sort by Latitude from N to S\n");
    printf("4. Sort by Longitude from E to W\n");
    printf("5. Return Main Menu\n");

    readInteger(&cmp);
    if(cmp < 1 || 4<cmp) return;
    Airport * l = mapValues(airports);
    for(int i = 0; i < size; i++){
        for( int j = 0; j < size-i-1; j++){
            if(apcmp(l[j], l[j+1], cmp)){
                Airport aux = l[j+1];
                l[j+1] = l[j];
                l[j] = aux;
            }
        }
    }

    printf("\n---- Airports -----------------\n");
    printf("%-15s %-60s %-35s %-10s %-15s %-15s %-s\n", "Iata Code", "Name", "City", "State", "Latitude", "Longitude", "Timezone");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for(int i = 0; i<size; i++){
        airportPrint(l[i]);
    }    

    free(l);   
}


void funcAirports(PtMap airports, PtList flights){
    int sizeMap, sizeList;
    if(mapSize(airports, &sizeMap)!= MAP_OK) return;
    if(listSize(flights, &sizeList)!=LIST_OK) return;
    Airport * l = mapValues(airports);
    Flight f;
    int numFlights[sizeMap], numDepDelays[sizeMap];
    float avgDepDelays[sizeMap];

    for(int i = 0; i<sizeMap; i++){
        numFlights[i] = 0;
        numDepDelays[i] = 0;
        avgDepDelays[i] = 0;
    }

    for (int i = 0; i<sizeList; i++){
        if(listGet(flights, i, &f)!=LIST_OK) return;
        for(int j = 0; j<sizeMap; j++){
            if(equalsStringIgnoreCase(l[j].iataCode, f.originAirport)){
                numFlights[j] += 1;
                if(f.departureDelay>15){
                    numDepDelays[j]+=1;
                    avgDepDelays[j] += f.departureDelay;
                }
            }
            if(equalsStringIgnoreCase(l[j].iataCode, f.destinationAirport)){
                numFlights[j] += 1;
            }
        }
    }

    printf("\n---- Airports ----------\n\n");
    printf("%-15s %-60s %-35s %25s %25s %25s\n", "Iata Code", "Name", "City", "Number Flights", "Num. Departure Delays", "Avg. Departure Delays");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    int numPrinted = 0, numDepDel = 0;
    float totalDepDel = 0;
    for(int i = 0; i<sizeMap; i++){
        if(numFlights[i]==0) continue;
        avgDepDelays[i] /= (float)numDepDelays[i];
        printf("%-15s %-60s %-35s %21d %25d %25f\n", l[i].iataCode, l[i].airport, l[i].city, numFlights[i], numDepDelays[i], avgDepDelays[i]);
        numDepDel+=numDepDelays[i];
        totalDepDel+=avgDepDelays[i];
        numPrinted++;
    }
    printf("\n%-15s %-60s %-35s %-25s %-25d %-25f\n", "", "ALL AIRPORTS", "", "", numDepDel, totalDepDel/(float)numPrinted);
    free(l);
}


void showAP(PtAirline * airlines, PtList flights, int sizeAirlines) {
    
    PtMap airports = mapCreate();
    int sizeFlights;
    listSize(flights, &sizeFlights);
    int sizeMap;
    MapKey* keys[sizeMap];
    
    for (int i = 0; i < sizeAirlines; i++) {
        int count = 0;
        for (int j = 0; j < sizeFlights; j++) {
            Flight f;
            listGet(flights, j, &f);
            if (equalsStringIgnoreCase(airlines[i]->iatacode, f.airline)) {
                if (!mapContains(airports, stringCodeCreate(f.originAirport))) {
                    mapPut(airports, stringCodeCreate(f.originAirport), airportCreate(f.originAirport, "", "", "", 0, 0, 0));
                    count++;
                }
            }
        }
        printf("%s passes through %d airports\n", airlines[i]->name, count);
        mapSize(airports, &sizeMap);
        if (count == 0) {
            printf("( no airports )\n");
        }
        else {    
            for (int k = 0; k < sizeMap; k++) {
                    mapKeyPrint(mapKeys(airports)[k]);
                    printf("\n");
            }
        }
        
        mapClear(airports);
    }
    mapDestroy(&airports);
}

double AverageGlobal(PtList flights){
    int size;
    listSize(flights, &size);
    int sum = 0;

        for(int i = 0; i < size; i++){
            Flight f;
            listGet(flights, i, &f);
            sum += f.distance;
        }
        return (sum/(double)size); 
}

double AverageWeek(PtList flights){
    int size;
    listSize(flights, &size);
    int sum = 0;
    int count = 0;

        for(int i = 0; i < size; i++){
            Flight f;
            listGet(flights, i, &f);
            if(f.dayOfWeek == 1 || f.dayOfWeek == 2 || f.dayOfWeek == 3 || f.dayOfWeek == 4 || f.dayOfWeek == 5){
                sum += f.distance;
                count++;
            }
        }
        return (sum/(double)count); 
}

double AverageWeekend(PtList flights){
    int size;
    listSize(flights, &size);
    int sum = 0;
    int count = 0;

        for(int i = 0; i < size; i++){
            Flight f;
            listGet(flights, i, &f);
            if(f.dayOfWeek == 6 || f.dayOfWeek == 7){
                sum += f.distance;
                count++;
            }
        }
        return (sum/(double)count); 
}

double AverageGlobalAirports(PtList flights, String airport){
    int size;
    listSize(flights, &size);
    int sum = 0;
    int count = 0;

        for(int i = 0; i < size; i++){
            Flight f;
            listGet(flights, i, &f);
            if (equalsStringIgnoreCase(f.originAirport, airport)){
                sum += f.distance;
                count++;
            }
        }
        return (sum/(double)count); 
}

double AverageWeekAirports(PtList flights, String airport){
    int size;
    listSize(flights, &size);
    int sum = 0;
    int count = 0;

        for(int i = 0; i < size; i++){
            Flight f;
            listGet(flights, i, &f);
            if(f.dayOfWeek == 1 || f.dayOfWeek == 2 || f.dayOfWeek == 3 || f.dayOfWeek == 4 || f.dayOfWeek == 5){
                if (equalsStringIgnoreCase(f.originAirport, airport)){
                    sum += f.distance;
                    count++;
                }
            }
        }
        return (sum/(double)count); 
}

double AverageWeekendAirports(PtList flights, String airport){
    int size;
    listSize(flights, &size);
    int sum = 0;
    int count = 0;

        for(int i = 0; i < size; i++){
            Flight f;
            listGet(flights, i, &f);
            if(f.dayOfWeek == 6 || f.dayOfWeek == 7){
                if (equalsStringIgnoreCase(f.originAirport, airport)){
                sum += f.distance;
                count++;
                }
            }
        }
        return (sum/(double)count); 
}

void Average(PtList flights, String airport){
    printf("Airport | All Days | Only Days of Week | Weekend\n");
    printf("   *       %.2f\t  %.2f\t %.2f\n", AverageGlobal(flights), AverageWeek(flights), AverageWeekend(flights));
    printf("  %s      %.2f\t  %.2f\t %.2f\n", airport, AverageGlobalAirports(flights, airport), AverageWeekAirports(flights, airport), AverageWeekendAirports(flights, airport));
}
