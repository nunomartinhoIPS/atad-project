#include "flight.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stringCode.h"

void flightPrint(PtFlight f){
    printf(
		"Flight: %d, \nOrigin: %s, \nDestination: %s, \nAirline: %s, \nDistance: %d, \nDay: %d, \nDay of the Week: %d, \nScheduled Departure: ", 
		f->flightNumber,
		f->originAirport,
		f->destinationAirport,
		f->airline,
		f->distance,
		f->day,
		f->dayOfWeek
	);
	printTime(f->scheduledDeparture);
	printf("\nDeparture Time: ");
	printTime(f->departureTime);
	printf("\nDeparture Delay: %d, \nScheduled Travel Time: %d", f->departureDelay, f->scheduledTravelTime);
	printf("\nScheduled Arrival: ");
	printTime(f->scheduledArrival);
	printf("\nArrival Time: ");
	printTime(f->arrivalTime);
	printf("\nArrival Delay: %d", f->arrivalDelay);
}

Flight flightCreate(int day, int dayOfWeek, char* airline, int flightNumber, char* originAirport, char* destinationAirport, Time scheduledDeparture, Time departureTime, 
                    int departureDelay, int scheduledTravelTime, int distance, Time scheduledArrival, Time arrivalTime, int arrivalDelay) {
    Flight f;
    
    f.day = day;
    f.dayOfWeek = dayOfWeek;
    strcpy(f.airline, airline);
    f.flightNumber = flightNumber;
    strcpy(f.originAirport, originAirport);
    strcpy(f.destinationAirport, destinationAirport);
    f.scheduledDeparture = scheduledDeparture;
    f.departureTime = departureTime;
    f.departureDelay = departureDelay;
    f.scheduledTravelTime = scheduledTravelTime;
    f.distance = distance;
    f.scheduledArrival = scheduledArrival;
    f.arrivalTime = arrivalTime;
    f.arrivalDelay = arrivalDelay;
    return f;

}