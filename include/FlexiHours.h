////////////////////////////
// This module contains an interface for
// time which the flexi calculations
// will use.
// HH:MM where HH can be as high as possible in a month, MM is 0-60.
//
#ifndef FLEXIHOURS_INCLUDED
#define FLEXIHOURS_INCLUDED

typedef int flxhour;
typedef int flxminute;

typedef struct flxFlexiHour
{
    flxhour hours;
    flxminute minutes;
    int initMagicNumber;   // when initialised this will have a magic value
} flxFlexiHour;

typedef enum kResult
{
    FAIL = 0,
    SUCCESS = 1
} kResult;

// checks if flxFlexiHour is initialised
int flxIsInitialised(const flxFlexiHour* flx);

// prints flexihour to stdout as HH:MM
int flxprint(const flxFlexiHour* flexihour);  

// Initializes flxFlexiHour struct with the minutes and hours passed in
// must use this before using this module
// Ret 1 if success, 0 if error
int flxUpdate(flxFlexiHour* ret, flxhour hours, flxminute minutes);

// converts struct to minutes
// return 1 if success, 0 if error
// places output to retMinute
int flxTimeToMin(const flxFlexiHour* flexihour, flxminute* retMinute);

// Converts minutes value to struct
// return 1 if success, 0 if error
// places output to retFlexiHours
int flxMinToTimeStruct(flxminute minute, flxFlexiHour* retFlexiHours);

#endif