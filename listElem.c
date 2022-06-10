#include <stdio.h>
#include "listElem.h"
#include "time.h"

void listElemPrint(ListElem elem) {
	printf(
		"Flight: %d, \nOrigin: %s, \nDestination: %s, \nAirline: %s, \nDistance: %d, \nDay: %d, \nDay of the Week: %d, \nScheduled Departure: ", 
		elem->flightNumber,
		elem->originAirport,
		elem->destinationAirport,
		elem->airline,
		elem->distance,
		elem->day,
		elem->dayOfWeek
	);
	printTime(elem->scheduledDeparture);
	printf("\nDeparture Time: ");
	printTime(elem->departureTime);
	printf("\nDeparture Delay: %d, \nScheduled Travel Time: %d", elem->departureDelay, elem->scheduledTravelTime);
	printf("\nScheduled Arrival: ");
	printTime(elem->scheduledArrival);
	printf("\nArrival Time: ");
	printTime(elem->arrivalTime);
	printf("\nArrival Delay: %d", elem->arrivalDelay);
}