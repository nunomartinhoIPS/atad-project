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
#include <ctype.h>

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
	memset( airlines, '\0', sizeof( airlines ) );
	
	/* creating map for Airports */
	int sizeAirports = 0;
	PtMap airports = NULL;
	
	/* creating list for flights */
	int sizeFlights = 0;
	PtList flights = NULL;

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
			if (!mapIsEmpty(airports)) {
				printf("Airports already loaded.");
			}
			else {
				if (mapDestroy(&airports) == MAP_NULL) {
					airports = mapCreate();
				}
					oLoadAP(airports);
					mapSize(airports, &sizeAirports);
			}
			flag = false;
			waitFunction();
		}

		if(equalsStringIgnoreCase(command, "LOADF")){
			if (mapIsEmpty(airports)) {
				printf("Load airports first (COMMAND: LOADAP).\n");
			}
			else {
				if (!listIsEmpty(flights)) printf("Flights already loaded.");
				else {
					if (listDestroy(&flights) == LIST_NULL) flights = listCreate();
					oLoadF(flights, airports);
					listSize(flights, &sizeFlights);
				}
			}
			flag = false;
			waitFunction();
		}
		if(equalsStringIgnoreCase(command, "LOADALL")){
			if (!listIsEmpty(flights) || !mapIsEmpty(airports)) printf("Files already loaded.");
			else {
				airports = mapCreate();
				flights = listCreate();
				oLoadAR(airlines, sizeAirlines);
				oLoadAP(airports);
				oLoadF(flights, airports);
				mapSize(airports, &sizeAirports);
				listSize(flights, &sizeFlights);
			}
			flag = false;
			waitFunction();
		}

		if (equalsStringIgnoreCase(command, "SHOWALL")){
			if (listIsEmpty(flights)) {
				printf("No Data Imported");
				flag = false;
			}else {
				showAll(flights);	
			} 
			flag = false;
			waitFunction();
		}
		if (equalsStringIgnoreCase(command, "SHOWAP")){
			if (listIsEmpty(flights) || airlines[0] == '\0') {
				printf("No Data Imported");
				flag = false;
			}else {
				showAP(airlines, flights, sizeAirlines);
				flag = false;
			}
				waitFunction();	
		}

		if (equalsStringIgnoreCase(command, "LISTAR")){
			if(listIsEmpty(flights) || airlines[0] == '\0'){
				printf("No Data Imported");
			}else{
				printf("\n----------LISTAR---------- \n\n");
				printf("\n-----List of Airlines----- \n\n");
				listAR(airlines, sizeAirlines, flights);

			}	
			flag = false;
			waitFunction();
		}
		if (equalsStringIgnoreCase(command, "LISTAP")){
			if(listIsEmpty(flights) || mapIsEmpty(airports)){
				printf("No Data Imported");
			}else{
				printf("\n----------LISTAP---------- \n\n");
				printf("\n-----List of Airports----- \n\n");
				listAP(airports, flights);
			}
			flag = false;
			waitFunction();
		}
		if (equalsStringIgnoreCase(command, "TOPN")){
			if(listIsEmpty(flights)){
				printf("No Data Imported");
			}else{
				int n=0;
				printf("\nInsert a number between 1 and 11515: ");
				readInteger(&n);
				while(n<1 || n>11515){
					printf("\nInvalid Number Try Again: ");
					readInteger(&n);
				}
				
				printf("\n----------TOPN---------- \n\n");
				
				printf("\nDay  Day of Week  Airline  Flight Number  Origin  Destination  Scheduled Departure  Departure Time  Scheduled Time  Distance  Scheduled Arrival  Arrival Time  Arrival Delay");
				topN(flights, n);
			}
			flag = false;
			waitFunction();
		}
		if (equalsStringIgnoreCase(command, "SHOWF")){
			String airport;
			if(listIsEmpty(flights)){
				printf("No Data Imported");
			}else{
				printf("\nInsert Airport Iata Code: ");
				fgets(airport, sizeof(airport), stdin);
				airport[strlen(airport) - 1] = '\0';
				printf("\n----------SHOWF---------- \n\n");
				printf("\nDay  Day of Week  Airline  Flight Number  Origin  Destination  Scheduled Departure  Departure Time  Scheduled Time  Distance  Scheduled Arrival  Arrival Time  Arrival Delay");
				showF(flights, airport);
			}
			flag = false;
			waitFunction();
		}

		if (equalsStringIgnoreCase(command, "ONTIME")){
			if(listIsEmpty(flights) || airlines[0] == '\0'){
				printf("No Data Imported");
			}
			else {
				onTime(airlines, sizeAirlines, flights);
			}
			flag = false;
			waitFunction();
		}

		if (equalsStringIgnoreCase(command, "AIRPORT_S")){
			if(mapIsEmpty(airports)){
				printf("No Data Imported");
			}
			else {
				airport_s(airports);
			}
			flag = false;
			waitFunction();
		}

		if (equalsStringIgnoreCase(command, "AIRPORTS")){
			if(listIsEmpty(flights) || mapIsEmpty(airports)){
				printf("No Data Imported");
			}else {
				funcAirports(airports, flights);
			}
			flag = false;
			waitFunction();
		}

		if (equalsStringIgnoreCase(command, "AVERAGE")){
			if(listIsEmpty(flights) || mapIsEmpty(airports)){
				printf("No Data Imported");
			}else {
				String airport, upper;
				printf("\nInsert Airport Iata Code: ");
				fgets(airport, sizeof(airport), stdin);
				airport[strlen(airport) - 1] = '\0';

				for(int i=0; i<strlen(airport); i++) {
					upper[i] = toupper(airport[i]);
				} 

				while (!mapContains(airports, stringCodeCreate(upper))) {
					printf("\nInvalid Iata Code please insert another: ");
					fgets(airport, sizeof(airport), stdin);
					airport[strlen(airport) - 1] = '\0';
					for(int i=0; i<strlen(airport); i++) {
						upper[i] = toupper(airport[i]);
					} 
				}
				
				Average(flights, airport);
			}
			flag = false;
			waitFunction();
			
		}

		if (equalsStringIgnoreCase(command, "CLEAR")){
			clearMemory(airlines, &airports, &flights, sizeAirlines);
			printf("\n<%d> records deleted from Airlineds", sizeAirlines);
        	printf("\n<%d> records deleted from Airports", sizeAirports);
        	printf("\n<%d> records deleted from Flights", sizeFlights);
			mapSize(airports, &sizeAirports);
			listSize(flights, &sizeFlights);
			flag = false;
			waitFunction();
		}
		if (equalsStringIgnoreCase(command, "QUIT")) {
			clearMemory(airlines, &airports, &flights, sizeAirlines);
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
	//system("clear");
	printf("\n===================================================================================");
	printf("\n\t\t\tPROJECT: United States Domestics Flight Data");
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