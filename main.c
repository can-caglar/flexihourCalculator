// Flexi hour calculator
//
// Can Caglar 26th March 2022
//
// TODO: Add a test folder which includes test files (stdin the tests, add asserts for tests)
// TODO: Get main algo to work!
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <limits.h>
#include "FlexiHours.h"

// Returns error or returnInt
// error is -1
int fgeti(FILE* fp, int* retInt)
{
    // Function which asks user to enter an integer
    #define MAX_LEN 13
    *retInt = 0;
    int retErr = 0;
    // First get line as a string
    char str[MAX_LEN] = { 0 };
    if (fgets(str, MAX_LEN, fp) == NULL)
    {
        puts("fgeti - Failed to read from filepointer.");
        retErr = -1;
    }
    long tempVal = 0;
    if (retErr != -1)
    {
        // we have potential string, let's convert it to a long
        char* endPtr;
        errno = 0;  // reset error
        tempVal = strtol(str, &endPtr, 0);
        // Error check
        if (str == endPtr)
        {
            puts("fgeti - No character was read.");
            retErr = -1;
        }
        else if (*endPtr && *endPtr != '\n')
        {
            puts("fgeti - Could not read the whole input. Failing...");
            retErr = -1;
        }
        else if (errno == ERANGE)
        {
            // Out of long range
            puts("fgeti - The entered integer is either too low or too high!");
            retErr = -1;
        }
        else
        {
            if (tempVal >= INT_MIN && tempVal <= INT_MAX)
            {
                // Got a number
                *retInt = tempVal;
                retErr = 0;
            }
            else
            {
                // Out of int range
                puts("fgeti - The entered integer is either too low or too high!");
                retErr = -1;
            }
        }
    }
    return retErr;
}


void getTimeFromUser(flxFlexiHour* time)
{
    // scanf("%d", &time->hours);
    int userHours, userMinutes;
    printf("Enter hours: ");
    while (fgeti(stdin, &userHours) == -1 || userHours < 0)
    {
        puts("Please try inserting a positive integer again.");
    }
    printf("Hours entered: %d. Now enter minutes: ", userHours);
    while (fgeti(stdin, &userMinutes) == -1 || userMinutes < 0)
    {
        puts("Please try inserting a positive integer again.");
    }
    printf("Minutes entered: %d\n", userMinutes);
    flxUpdate(time, userHours, userMinutes);
    printf("Got: ");
    flxprint(time);
}

int main()
{
    puts("Welcome to flexicalc!");

    flxFlexiHour flexiReduced, flexiGained, givingBack, workDays;
    flxUpdate(&flexiReduced, 0, 0);
    flxUpdate(&flexiGained, 0, 0);
    flxUpdate(&givingBack, 0, 0);
    flxUpdate(&workDays, 7, 30);

    // Ask for flexi hours reduced
    printf("First entering \"flexi reduced\" time. ");
    getTimeFromUser(&flexiReduced);
    printf("Next entering \"flexi gained\" time. ");
    getTimeFromUser(&flexiGained);

    // Debug
    printf("Reduced hours: ");
    flxprint(&flexiReduced);
    printf("Gained hours: ");
    flxprint(&flexiGained);
    // Debug end

    // Ask for how many full days left to work
    printf("Enter full work days left: ");
    int workDaysLeft;
    while (fgeti(stdin, &workDaysLeft) == -1 || workDaysLeft < 0)
    {
        printf("Please insert a positive integer: ");
    }
    printf("Work days left recevied = %d\n", workDaysLeft);

    // Do calculation
    flxminute dailyMinutes, minsLeftToWork, minsReduced, minsGained;

    flxTimeToMin(&flexiReduced, &minsReduced);
    flxTimeToMin(&flexiGained, &minsGained);
    flxTimeToMin(&workDays, &dailyMinutes);
    minsLeftToWork = dailyMinutes * workDaysLeft;

    printf("Mins reduced: %d | Mins gained: %d | Mins left to work: %d | Daily mins: %d\n",
        minsReduced,
        minsGained,
        minsLeftToWork,
        dailyMinutes);

    flxminute trueMinsReduced = minsReduced - minsLeftToWork;
    flxminute currentBalance = minsGained - trueMinsReduced;
    flxminute perDay = currentBalance / workDaysLeft;
    printf("Current balance = %d\n", currentBalance);
    if (perDay >= 0)
    {
        printf("In credit: ");
    }
    else
    {
        perDay *= -1;   // modularise
        printf("In debt: ");
    }
    printf("%d minutes over %d day(s). \n", perDay, workDaysLeft);
    return 0;
}