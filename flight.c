#include "flight.h"

void showF(PtList list)
{
}

void showAllPaged(PtList list)
{

    String command;
    int page = 0;
    int exit = 0;
    PtFlight flight;
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
            listGet(list, i, flight);
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

void showAllSample(PtList list)
{
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

void printFlightsMenu()
{
    clrscr(); // clear console.
    printf("\n===================================================================================");
    printf("\n\t\t\t\t\t\t\t\t\tALL FLIGHTS");
    printf("\n===================================================================================");
}