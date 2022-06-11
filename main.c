#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "utils.h"
#include "list.h"
#include "map.h"
#include "input.h"
#include "loaders.h"
#include "operations.h"

void printCommandsMenu();
void waitFunction();


int main() {
	srand(time(NULL));

	/* commands interpreter */
	String command;
	int quit = 0;

	setlocale(LC_ALL, "PT");

	/* creating airlines array */
	int sizeAirlines;
	sizeOfLoadAR(&sizeAirlines);
	PtAirline airlines[sizeAirlines];

	/* creating map for Airports */
	int sizeAirports;
	PtMap airports = mapCreate();
	mapSize(airports, &sizeAirports);
	//if(airports == NULL) printf("fodase");
	
	/* creating list for flights */
	int sizeFlights;
	PtList flights = listCreate();
	listSize(flights, &sizeFlights);

	while (!quit){
		printCommandsMenu();
		bool flag = true;
		fgets(command, sizeof(command), stdin);
		/* descartar 'newline'. Utilizar esta técnica sempre que for lida uma
		 * string para ser utilizada, e.g., nome de ficheiro, chave, etc.. */
		command[strlen(command) - 1] = '\0';
		if (equalsStringIgnoreCase(command, "LOADAR")){
			int errorCode = loadAR(airlines, sizeAirlines);
			if(errorCode == LOADER_OK)
				printf("<%d> airline records imported\n", sizeAirlines);
			if(errorCode == LOADER_FILE_NOT_FOUND)
				printf("File not found");
			flag = false;
			waitFunction();
		}
		if(equalsStringIgnoreCase(command, "LOADAP")){
			int errorCode = loadAP(airports);
			int mapErrorcode = mapSize(airports, &sizeAirports);
			if(mapErrorcode!=MAP_OK) {
				printf("Something went wrong with the Map of StringCode to Airports, error: %d\n", mapErrorcode);
				continue;
			}
			if(errorCode == LOADER_OK)
				printf("<%d> airport records imported\n", sizeAirports);
			if(errorCode == LOADER_FILE_NOT_FOUND)
				printf("File not found");
			flag = false;
			//mapPrint(airports);
			waitFunction();
		}
		if (equalsStringIgnoreCase(command, "SHOWALL")){
			    
			printf("\nCOMMADS: ALL, SAMPLE, \n");
    		printf("COMMAND>");
			
			fgets(command, sizeof(command), stdin);
			command[strlen(command) - 1] = '\0';

    		if (equalsStringIgnoreCase(command, "ALL")){
        		//showAllPaged();
    		}
			
			if (equalsStringIgnoreCase(command, "SAMPLE")){
        		//showAllSample();
    		}

			flag = false;
			waitFunction();
		}
		if (equalsStringIgnoreCase(command, "CLEAR")){
			printf("<%d> records deleted from <Flights | Airports |Airlines>", sizeAirlines + sizeAirports + sizeFlights);
			clearAll(airlines, airports, flights, sizeAirlines);
			flag = false;
			waitFunction();
		}
		if (equalsStringIgnoreCase(command, "QUIT")){
			clearAll(airlines, airports, flights, sizeAirlines);
			quit = 1; /* vai provocar a saída do interpretador */
			flag = false;
		}
		if(flag){
			printf("Command not found!\n");
			waitFunction();
		}
	}

	printf("Good Bye! ...\n");
}

void printCommandsMenu(){
	printf("\n===================================================================================");
	printf("\n                          PROJECT: United States Domestics Flight Data");
	printf("\n===================================================================================");
	printf("\nA. Base commands (LOADAR, LOADAP, LOADF, CLEAR).");
	printf("\nB. Aggregated info about flights (SHOWALL, SHOWF, LISTAR, LISTAP, ONTIME, AVERAGE,");
	printf("\n   SHOWAP, TOPN, TSP).");
	printf("\nC. Complex Indicators require airports and flights data (AIRPORT_S, AIRPORTS).");
	printf("\nD. Exit (QUIT)\n\n");
	printf("COMMAND> ");
}

void waitFunction(){
	printf("\nPress enter to continue ...");
	getchar();
}