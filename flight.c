#include "flight.h"

void flightPrint(PtFlight f){
    printf("\n%d\t\t%d\t\t%s\t\t%d\t\t%s\t\t%s\t\t", f->day, f->dayOfWeek, f->airline, f->flightNumber, f->originAirport, f->destinationAirport);
    timePrint(f->scheduledDeparture);
    printf("\t\t");
    timePrint(f->departureTime);
    printf("\t\t%d\t\t%d\t\t", f->scheduledTravelTime, f->distance);
    timePrint(f->scheduledArrival);
    printf("\t\t");
    timePrint(f->arrivalTime);
    printf("\t\t%d\t\t", f->arrivalDelay);
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