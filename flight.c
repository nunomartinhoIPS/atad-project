#include "flight.h"

void flightPrint(PtFlight f){
    printf("\n%-10d%-10d%-12s%-11d%-11s%-10s     ", f->day, f->dayOfWeek, f->airline, f->flightNumber, f->originAirport, f->destinationAirport);
    timePrint(f->scheduledDeparture);
    printf("%14s", "");
    timePrint(f->departureTime);
    printf("%10s", "");
    printf("%5d%14d%10s", f->scheduledTravelTime, f->distance, "");
    timePrint(f->scheduledArrival);
    printf("%-12s", "");
    timePrint(f->arrivalTime);
    printf("%-10s", "");
    printf("%-1d", f->arrivalDelay);
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