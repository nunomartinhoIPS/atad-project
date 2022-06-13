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
			oLoadAR(airlines, sizeAirlines);
			flag = false;
			waitFunction();
		}
		if(equalsStringIgnoreCase(command, "LOADAP")){
			oLoadAP(airports);
			mapSize(airports, &sizeAirports);
			flag = false;
			waitFunction();
		}

		if(equalsStringIgnoreCase(command, "LOADF")){
			oLoadF(flights);
			listSize(flights, &sizeFlights);
			flag = false;
			waitFunction();
		}

		if (equalsStringIgnoreCase(command, "SHOWALL")){
			    
			printf("\n< COMMADS: ALL, SAMPLE >\n");
    		printf("COMMAND>");
			
			fgets(command, sizeof(command), stdin);
			command[strlen(command) - 1] = '\0';

    		if (equalsStringIgnoreCase(command, "ALL")){
        		showAllPaged(flights);
    		}
			
			if (equalsStringIgnoreCase(command, "SAMPLE")){
        		showAllSample(flights);
    		}

			flag = false;
			waitFunction();
		}
		
		if (equalsStringIgnoreCase(command, "CLEAR")){
			printf("<%d> records deleted from <Flights | Airports | Airlines>", sizeAirlines + sizeAirports + sizeFlights);
			if (sizeAirlines > 0 && !mapIsEmpty(airports) && !listIsEmpty(flights)) {
				clearAll(airlines, airports, flights, sizeAirlines);
			}
			flag = false;
			waitFunction();
		}
		if (equalsStringIgnoreCase(command, "QUIT")){
			if (sizeAirlines > 0 && !mapIsEmpty(airports) && !listIsEmpty(flights)) {
				clearAll(airlines, airports, flights, sizeAirlines);
			}
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
	system("clear");
}