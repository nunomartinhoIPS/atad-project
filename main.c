#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "utils.h"
#include "list.h"
#include "map.h"
#include "input.h"
#include "loaders.h"

void printCommandsMenu();
void waitFunction();

int main()
{

	srand(time(NULL));

	/* commands interpreter */
	String command;
	int quit = 0;

	setlocale(LC_ALL, "PT");

	// creating airlines array
	int size;
	sizeOfLoadAR(&size);
	PtAirline airlines[size];

	while (!quit){
		printCommandsMenu();
		bool flag = true;
		fgets(command, sizeof(command), stdin);
		/* descartar 'newline'. Utilizar esta técnica sempre que for lida uma
		 * string para ser utilizada, e.g., nome de ficheiro, chave, etc.. */
		command[strlen(command) - 1] = '\0';
		if (equalsStringIgnoreCase(command, "LOADAR")){
			
			LoadAR(airlines, size);
			for(int i = 0; i<size; i++)
				airlinePrint(airlines[i]);
			flag = false;
			waitFunction();
		}

		if (equalsStringIgnoreCase(command, "SHOWALL")){
			    
			printf("\nCOMMADS: ALL, SAMPLE, \n");
    		printf("commad>");
			
			fgets(command, sizeof(command), stdin);
			command[strlen(command) - 1] = '\0';

    		if (equalsStringIgnoreCase(command, "ALL")){
        		//paginas
    		}
			
			if (equalsStringIgnoreCase(command, "SAMPLE")){
        		//sample
    		}

			flag = false;
			waitFunction();
		}
		if (equalsStringIgnoreCase(command, "QUIT")){
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

void printCommandsMenu()
{
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

void waitFunction()
{
	printf("\nPress enter to continue ...");
	getchar();
}
