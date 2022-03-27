#include "FlexiHours.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

#define INITMAGICNUMBER 776655333

// Static functions
static void updateTime(flxFlexiHour* ret, flxhour hours, flxminute minutes);

// Initializes flxFlexiHour struct with the minutes and hours passed in
// must use this before using this module
// Ret 1 if success, 0 if error
int flxUpdate(flxFlexiHour* ret, flxhour hours, flxminute minutes)
{
    int success = SUCCESS;
    // Error checking
    if (ret == NULL || hours < 0 || minutes < 0)
    {
        printf("flxUpdate - Bad arg(s), ret = 0x%p, hours = %d, minutes = %d\n",
            ret,
            hours,
            minutes);
        printf("Original flx = %d %d %d\n", 
            ret->hours, 
            ret->minutes,
            ret->initMagicNumber);
        success = FAIL;
    }
    else
    {
        ret->initMagicNumber = INITMAGICNUMBER;
        updateTime(ret, hours, minutes);
    }
    return success;
}

int flxIsInitialised(const flxFlexiHour* flx)
{
    return flx && flx->initMagicNumber == INITMAGICNUMBER;
}

// prints flexihour to stdout as HH:MM
int flxprint(const flxFlexiHour* flexihour)
{
    int success = SUCCESS;
    if (flxIsInitialised(flexihour))
    {
        if (flexihour->minutes >= 60)  // print weird values
        {
            printf("%d:%d\n", flexihour->hours, flexihour->minutes);
        }
        else  // print ordinary time values
        {
            printf("%d:%02d\n", flexihour->hours, flexihour->minutes);
        }
    }
    else
    {
        printf("Cannot print uninitialised flxFlexiHour struct!\n");
        success = FAIL;
    }
    return success;
}

// Adjusts the flxFlexiHour struct to correct time values i.e. if minutes > 60
// will move excess time to hours
// Ret 1 if success, 0 if error
static void updateTime(flxFlexiHour* ret, flxhour hours, flxminute minutes)
{
    // Calculation
    flxhour hoursFromMins = (flxhour)ceil(minutes / 60);
    hours += hoursFromMins;
    minutes %= 60;
    // Assigning
    ret->hours = hours;
    ret->minutes = minutes;
}

// converts struct to minutes
// return 1 if success, 0 if error
// places output to retMinute
int flxTimeToMin(const flxFlexiHour* flexihour, flxminute* retMinute)
{
    int success = SUCCESS;
    if (flxIsInitialised(flexihour))
    {
        // Calculation
        flxminute min = flexihour->hours * 60;
        min += flexihour->minutes;
        // Assignment
        *retMinute = min;
    }
    else
    {
        puts("flxTimeToMin - Failed, struct not initialised");
        success = FAIL;
    }
    return success;
}

// Converts minutes value to struct
// return 1 if success, 0 if error
// places output to retFlexiHours
int flxMinToTimeStruct(flxminute minute, flxFlexiHour* retFlexiHours)
{
    int success = SUCCESS;
    if (minute >= 0)
    {
        flxhour hour = minute / 60;
        flxminute min = minute % 60;
        success = flxUpdate(retFlexiHours, hour, min);
    }
    else
    {
        puts("flxMinToTimeStruct - Failed");
        success = FAIL;
    }
    return success;
}

