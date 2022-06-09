#include "flight.h"
#include "list.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "listElem.h"
#include "stringCode.h"

/*void printFlight(Flight f){
    listElemPrint(f);
}*/

void showF(PtList list){
    
}


void print20(PtList list){
   String s;
   fgets(s, sizeof(s), stdin);
   while(strcmp(s, "done")!= 0){
       printPages(list, page*20);
       waitForInput(list, &page);
   }
}

void showAllPaged(PtList list) {

    String command;
    int page = 0;
    int exit = 0;

    while (!exit) {
        clrscr();
        printf("\n===================================================================================");
        printf("\n                          ALL FLIGHTS");
        printf("\n===================================================================================");
        for (int i = page*20; i < (page+1)*20; i++) {
            listElemPrint(list->elements[i]);
        }
        printf("\nPAGE [%d]", page);
        printf("\nCommands  (NEXT, PREV, EXIT)");
        printf("\ncommand> ");
        fgets(command, sizeof(command), stdin);
        command[strlen(command) - 1] = '\0';

        if (equalsStringIgnoreCase(s, "NEXT")){
            page++;
        }

        if (equalsStringIgnoreCase(s, "PREV")){
            if (page > 0) page--;
        }

        if (equalsStringIgnoreCase(s, "EXIT")){
            exit = 1;
        }

    }
}

void showAllSample(PtList list) {
    
}