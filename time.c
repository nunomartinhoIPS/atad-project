#include "time.h"

Time timeCreate(int hour, int min){
    Time t;
    t.hour=hour;
    t.min=min;
    return t;
}

int timeDiff(Time time1,Time time2) {
    // if time2 goes after midnight and time is before midnight
    if (time2.hour < time1.hour)
        //time2.hour = 24-time2.hour;
        time2.hour = 24+time2.hour;
    return (time2.hour - time1.hour) * 60 + (time2.min - time1.min);
}


// Calculate the time difference between time1 and time2, in minutes
// timeDiffSpecial = time2-time1
int timeDiffSpecial(Time time1,Time time2) {
    int aux = (time2.hour - time1.hour) * 60 + (time2.min - time1.min);
    if (aux < -70) 
        aux = ( (time2.hour+24) - time1.hour) * 60 + (time2.min - time1.min);
    else if (aux > 1100) 
        aux = ( time2.hour - (time1.hour+24)) * 60 + (time2.min - time1.min);
    return aux;
}

void timePrint(Time t){
    if(t.hour>=10 && t.min>=10)
        printf("%d:%d", t.hour, t.min);
    else if(t.hour>=10 && t.min<10)   
        printf("%d:0%d", t.hour, t.min);
    else if(t.hour<10 && t.min>=10)
        printf("0%d:%d", t.hour, t.min);
    else
        printf("0%d:0%d", t.hour, t.min);
}

bool timePassedDay(Time t1, Time t2){
    return t1.hour>t2.hour;
}

int timeSum(Time * t1, Time t2){
    t1->hour+=t2.hour;
    t1->min+=t2.min;
    int hpassed=0;
    while(t1->min>=60){
        hpassed++;
        t1->min-=60;
    }
    t1->hour+=hpassed;
    int daysPassed=0;
    while(t1->hour>=24){
        daysPassed++;
        t1->hour-=24;
    }
    return daysPassed;
}
