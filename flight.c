#include "flight.h"
#include "list.h"
#include "airport.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void flightPrint(Flight f){
    printf(
		"Flight: %d, \nOrigin: %s, \nDestination: %s, \nAirline: %s, \nDistance: %d, \nDay: %d, \nDay of the Week: %d, \nScheduled Departure: ", 
		f.flightNumber,
		f.originAirport,
		f.destinationAirport,
		f.airline,
		f.distance,
		f.day,
		f.dayOfWeek
	);
	printTime(f.scheduledDeparture);
	printf("\nDeparture Time: ");
	printTime(f.departureTime);
	printf("\nDeparture Delay: %d, \nScheduled Travel Time: %d", f.departureDelay, f.scheduledTravelTime);
	printf("\nScheduled Arrival: ");
	printTime(f.scheduledArrival);
	printf("\nArrival Time: ");
	printTime(f.arrivalTime);
	printf("\nArrival Delay: %d", f.arrivalDelay);
}

void showF(PtList flights, char airport[4]){
    int count = 0;
    int * size = 0;
    listSize(flights, size);
    for(int i = 0; i<size; i++){
        Flight f;
        listGet(flights, i, &f);
        if(f.originAirport == airport){
            count++;
            flightPrint(f);
        }
    }
    if(count==0){
        printf("Flight data not available for %s.", airport);
    }
}