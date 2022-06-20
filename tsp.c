#include "tsp.h"

#define swap(a, b)             \
    do                         \
    {                          \
        typeof(a) __tmp = (a); \
        (a) = (b);             \
        (b) = __tmp;           \
    } while (0)

static PtList flightsOrderedByTime(PtList flights, int day, Time time)
{
    int size, count = 0;
    if (listSize(flights, &size) != LIST_OK)
        return NULL;
    PtList copy = listCreate();
    for (int i = 0; i < size; i++)
    {
        Flight f;
        listGet(flights, i, &f);
        if (f.day == day && (f.scheduledDeparture.hour > time.hour || (f.scheduledDeparture.hour == time.hour && f.scheduledDeparture.min >= time.min)))
            listAdd(copy, count++, f);
    }
    return copy;
}

static int flightsOrderByTimeAndAP(PtList flights, int day, Time time, char *o, char *d, int lastIndex)
{
    int size;
    if (listSize(flights, &size) != LIST_OK)
        return -1;
    for (int i = lastIndex; i < size; i++)
    {
        Flight f;
        listGet(flights, i, &f);
        if (
            f.day == day && (f.scheduledDeparture.hour > time.hour || (f.scheduledDeparture.hour == time.hour && f.scheduledDeparture.min >= time.min)) &&
            equalsStringIgnoreCase(f.originAirport, o) &&
            equalsStringIgnoreCase(f.destinationAirport, d))
            return i;
    }
    return -1;
}

static int totalDist(PtList flights)
{
    int size, total = 0;
    if (listSize(flights, &size) != LIST_OK)
        return 0;
    for (int i = 0; i < size; i++)
    {
        Flight f;
        listGet(flights, i, &f);
        total += f.distance;
    }
    return total;
}

static int totalTimeTraveling(PtList flights)
{
    int size, total = 0;
    if (listSize(flights, &size) != LIST_OK)
        return 0;
    for (int i = 0; i < size; i++)
    {
        Flight f;
        listGet(flights, i, &f);
        total += f.scheduledTravelTime - f.departureDelay + f.arrivalDelay;
    }
    return total;
}

static int totalTime(PtList flights)
{
    int size;
    if (listSize(flights, &size) != LIST_OK)
        return 0;
    Flight start, end;

    listGet(flights, 0, &start);
    listGet(flights, size - 1, &end);

    int timeStart = (start.day * 24 * 60) + (start.scheduledDeparture.hour * 60) + start.scheduledDeparture.min;
    int timeEnd = ((end.day) * 24 * 60) + (end.arrivalTime.hour * 60) + end.arrivalTime.min;
    if (timePassedDay(end.scheduledDeparture, end.scheduledArrival))
        timeEnd += (1 * 24 * 60);
    return timeEnd - timeStart;
}

static void perm(Airport *airports, int start, int end, StringCode *possibilities, int *possibilitiesSize)
{
    if (start == end)
    {
        StringCode s = stringCodeCreate("");
        for (int i = 0; i < end + 1; i++)
        {
            strcat(s.code, airports[i].iataCode);
            strcat(s.code, " ");
        }
        possibilities[(*possibilitiesSize)++] = s;
    }
    for (int i = start; i <= end; i++)
    {
        swap(*(airports + i), *(airports + start));
        perm(airports, start + 1, end, possibilities, possibilitiesSize);
        swap(*(airports + i), *(airports + start));
    }
}

static void calculate(StringCode permutation, Airport o, PtList flights, PtList path, PtList temporaryPath)
{
    int lastIndex = 0, strSize = 0;
    char *p = strtok(permutation.code, " ");
    char *tokens[10];
    while (p != NULL)
    {
        tokens[strSize++] = p;
        p = strtok(NULL, " ");
    }
    listClear(temporaryPath);
    int sizeTempPath;
    listSize(temporaryPath, &sizeTempPath);
    Flight f;
    listGet(flights, 0, &f);
    int dayStart = f.day;

    int index = flightsOrderByTimeAndAP(flights, dayStart, timeCreate(0, 0), o.iataCode, tokens[0], lastIndex);
    if (index == -1)
        return;
    lastIndex = index;
    listGet(flights, index, &f);
    listAdd(temporaryPath, sizeTempPath++, f);

    for (int i = 0; i < strSize; i++)
    {
        Flight aux;
        listGet(temporaryPath, sizeTempPath - 1, &aux);
        Time next = timeCreate(1, 30);
        int day = timeSum(&next, aux.scheduledArrival);
        int dayPassed = timePassedDay(aux.scheduledDeparture, f.scheduledArrival);
        day = f.day + day + dayPassed;
        int currIndex;
        if (i + 1 != strSize)
            currIndex = flightsOrderByTimeAndAP(flights, day, next, tokens[i], tokens[i + 1], lastIndex);
        else
            currIndex = flightsOrderByTimeAndAP(flights, day, next, tokens[i], o.iataCode, lastIndex);

        if (currIndex == -1)
            return;

        lastIndex = currIndex;
        listGet(flights, currIndex, &f);
        listAdd(temporaryPath, sizeTempPath++, f);
    }

    if (totalTimeTraveling(temporaryPath) < totalTimeTraveling(path))
    {
        listClear(path);
        for (int i = 0; i < sizeTempPath; i++)
        {
            listGet(temporaryPath, i, &f);
            listAdd(path, i, f);
        }
    }
}

static PtMap filterAP(PtMap airports, PtList flights)
{
    int sizeMap, sizeList;
    if (mapSize(airports, &sizeMap) != MAP_OK)
        return NULL;
    if (listSize(flights, &sizeList) != LIST_OK)
        return NULL;
    PtMap map = mapCreate();
    Flight f;
    Airport a;
    for (int i = 0; i < sizeList; i++)
    {
        listGet(flights, i, &f);
        if (!mapContains(map, stringCodeCreate(f.originAirport)))
        {
            mapGet(airports, stringCodeCreate(f.originAirport), &a);
            mapPut(map, stringCodeCreate(f.originAirport), a);
        }
        if (!mapContains(map, stringCodeCreate(f.destinationAirport)))
        {
            mapGet(airports, stringCodeCreate(f.destinationAirport), &a);
            mapPut(map, stringCodeCreate(f.destinationAirport), a);
        }
    }
    return map;
}

static int factorial(int n) {
    if (n>=1)
        return n*factorial(n-1);
    else
        return 1;
}

void tsp(PtList flights, PtMap tempAirports)
{
    PtMap airports = filterAP(tempAirports, flights);
    double time_spent = 0.0;
    printf("\n--------Airports--------------------------\n");
    Airport *a = mapValues(airports);
    int sizeAP;
    mapSize(airports, &sizeAP);
    for (int i = 0; i < sizeAP; i++)
    {
        printf("%3d | %s  -  %s\n", i, a[i].iataCode, a[i].airport);
    }
    printf("Input number of stating Airport.\nCOMAND>");
    int startingAirportIndex;
    readInteger(&startingAirportIndex);
    Airport start = a[startingAirportIndex];
    free(a);
    printf("\nOrigin Airport = %s\n", start.iataCode);
    printf("Input initial day.\nCOMAND>");
    int startDay, startHour, startMin;
    readInteger(&startDay);
    printf("Input initial hour and min.\nhour = ");
    readInteger(&startHour);
    printf("\nmin = ");
    readInteger(&startMin);

    Time startTime = timeCreate(startHour, startMin);

    int fact = factorial(sizeAP);
    StringCode *allPermutations;
    allPermutations = (StringCode *)calloc(fact, sizeof(StringCode));
    if (allPermutations == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }
    int allPermutationsSize = 0;
    // generate all permutations
    perm(mapValues(airports), 0, sizeAP - 1, allPermutations, &allPermutationsSize);

    // final and temporary path list
    PtList finalPath = listCreate();
    PtList tempPath = listCreate();

    /*------------------------------------------------------------------------------*/
    // list of filtered flights that departure after the specified day or on the specified day after the specified time
    // this is a pre filter to reduce the number of elements on the following cicles
    PtList filteredFlightsAfterDayAndHour = listCreate();
    int filteredFlightsAfterDayAndHourSize = 0;

    // filters the flights
    int originalSize;
    listSize(flights, &originalSize);
    for (int i = 0; i < originalSize; i++)
    {
        Flight flight;
        listGet(flights, i, &flight);

        // add flights that departure in the same day as specified and the schedule departure is equal ou greater than specified time
        // or flights that departure in the following days
        if ((flight.day > startDay && flight.day < startDay + 3) || (flight.day == startDay && (flight.scheduledDeparture.hour > startTime.hour || (flight.scheduledDeparture.hour == startTime.hour && flight.scheduledArrival.min >= startTime.min))))
        {
            listAdd(filteredFlightsAfterDayAndHour, filteredFlightsAfterDayAndHourSize++, flight);
        }
    }
    /*------------------------------------------------------------------------------*/
    clock_t begin = clock();
    printf("Calculating %d possibilities, this may take a while...\n", allPermutationsSize);
    for (int i = 0; i < allPermutationsSize; i++)
    {
        if (i % 1000 == 0)
        {
            printf("\r%d of %d already calculated", i, allPermutationsSize);
            fflush(stdout);
        }
        // printf("%d - ", i);
        // stringCodePrint(allPermutations[i]);
        calculate(allPermutations[i], start, filteredFlightsAfterDayAndHour, finalPath, tempPath);
    }
    printf("\n");

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    int finalPathSize;
    listSize(finalPath, &finalPathSize);
    if (finalPathSize != 0)
    {
        printf("Best path took %f seconds to be found\n", time_spent);

        printf("Day Day_of_Week Airline Flight_Number Origin Destionation Scheduled_Departure Departure_Time Dep_Dif Scheduled_Time Distance Scheduled_Arrival Arrival_Time Arr_Dif\n");
        listPrint(finalPath);
        printf("Total travel time = %d\n", totalTime(finalPath));
        printf("Total travel distance = %d\n", totalDist(finalPath));
        printf("Total time spent = %d\n", totalTimeTraveling(finalPath));
    }
    else
    {
        printf("After %f seconds no path as found with the specified params...\n", time_spent);
    }
    listDestroy(&tempPath);
    listDestroy(&finalPath);
    free(allPermutations);

    mapDestroy(&airports);
}
