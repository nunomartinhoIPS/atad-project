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
	memset( airlines, '\0', sizeof( airlines ) );
	
	/* creating map for Airports */
	int sizeAirports;
	PtMap airports = mapCreate();
	mapSize(airports, &sizeAirports);
	
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
		if(equalsStringIgnoreCase(command, "LOADALL")){
			oLoadAR(airlines, sizeAirlines);
			oLoadAP(airports);
			oLoadF(flights);
			mapSize(airports, &sizeAirports);
			listSize(flights, &sizeFlights);
			flag = false;
			waitFunction();
		}

		if (equalsStringIgnoreCase(command, "SHOWALL")){
			    
			showAll(flights);

			flag = false;
		}

		if (equalsStringIgnoreCase(command, "LISTAR")){
			printf("\nAirlines: \n\n");
			listAR(airlines, sizeAirlines, flights);
			flag = false;
			waitFunction();
		}
		if (equalsStringIgnoreCase(command, "TOPN")){
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
			flag = false;
			waitFunction();
		}
		if (equalsStringIgnoreCase(command, "SHOWF")){
			String airport;
			if(listIsEmpty(flights)){
				printf("No Data Imported");
				flag = false;
				waitFunction();
			}else{
				printf("\nInsert Airport Iata Code: ");
				fgets(airport, sizeof(airport), stdin);
				airport[strlen(airport) - 1] = '\0';
				printf("\n----------SHOWF---------- \n\n");
				printf("\nDay  Day of Week  Airline  Flight Number  Origin  Destination  Scheduled Departure  Departure Time  Scheduled Time  Distance  Scheduled Arrival  Arrival Time  Arrival Delay");
				showF(flights, airport);
				flag = false;
				waitFunction();
			}
		}

		if (equalsStringIgnoreCase(command, "ONTIME")){
			onTime(airlines, sizeAirlines, flights);
			flag = false;
			waitFunction();
		}

		if (equalsStringIgnoreCase(command, "AIRPORT_S")){
			airport_s(airports);
			flag = false;
			waitFunction();
		}

		if (equalsStringIgnoreCase(command, "CLEAR")){
			clearMemory(airlines, &airports, &flights, sizeAirlines);
			printf("\n<%d> records deleted from Airlines", sizeAirlines); //não gosto de ti luis >:(
			printf("\n<%d> records deleted from Airports", sizeAirports);
			printf("\n<%d> records deleted from Flights", sizeFlights);
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
	system("clear");
	printf("\n===================================================================================");
	printf("\n\t\t\tPROJECT: United States Domestics Flight Data");
	printf("\n===================================================================================");
	printf("\nA. Base commands (LOADAR, LOADAP, LOADF, LOADALL, CLEAR).");
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