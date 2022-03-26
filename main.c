// Flexi hour calculator
//
// Can Caglar 26th March 2022
//
// TODO: Separate the flexi library, update Makefile
// TODO: Add a test folder which includes test files (stdin the tests, add asserts for tests)
// TODO: Get main algo to work!
//
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <math.h>

typedef struct tFlexitime
{
    int hours;
    int minutes;
} tFlexitime;

typedef int seconds;

void flexiUpdateValues(tFlexitime* t, int hours, int minutes);

tFlexitime flexiInit(const int hours, const int minutes)
{
    tFlexitime ret;
    flexiUpdateValues(&ret, hours, minutes);
    return ret;
}

void flexiPrint(const tFlexitime* t)
{
    printf("%d:%d\n", t->hours, t->minutes);
}

void flexiUpdateValues(tFlexitime* t, const int hours, const int minutes)
{
    // todo, make it so passing minutes > 60 will append to hours.
    t->hours = hours;
    t->minutes = minutes;
}

// Returns error or returnInt
int* fgeti(int* returnInt)
{
    // First get all string from stdin
    char ret[50];
    fgets(ret, 50, stdin);
    ret[strcspn(ret, "\n")] = 0;  // clear \n

    // Convert str to long
    // TODO: @CC Continue here!
    char* errorChar;
    long returnLong = strtol(ret, errorChar, 10);
    if (ret != errorChar)
    {

    }
    else
    {
        returnInt = NULL;
    }

    return returnInt;
}

// Returns 0 if success, non-0 if error.
int getTimeFromUser(tFlexitime* retTime)
{
    printf("Enter HOURS: ");
    retTime->hours = fgeti() % 24;
    printf("Enter MINUTES: ");
    retTime->minutes = fgeti() % 60;
    return 0;
}

// Convert tFlexitime to seconds. return -1 if fail.
seconds flexiTimeToSeconds(const tFlexitime* time)
{
    seconds rets = -1;
    if (time)
    {
        rets = (time->hours * 60) + time->minutes;  // to minutes
        rets *= 60;   // to seconds
        rets = rets > 0 ? rets : -1;
    }
    return rets;
}

// Convert second to flexiTime, return -1 if fail
// Will discard unused seconds
int flexiSecondsToFlexitime(tFlexitime* ret, const seconds sec)
{
    int err = -1;
    if (ret)
    {
        int totalMinutes = (int)floor(sec / 60);    // convert seconds to minutes
        int hours = (int)floor(totalMinutes / 60);  // convert minutes to hours
        ret->hours = hours;
        ret->minutes = totalMinutes % 60;           // update remainder minutes
    }
    return err;
}

int main()
{
    // Prestart
    srand((unsigned)time(NULL));  // seed random
    // Prestart end

    puts("Welcome to flexicalc");

    tFlexitime flexiReduced = flexiInit(0, 0);
    tFlexitime flexiGained = flexiInit(0, 0);
    const tFlexitime workDays = flexiInit(7, 30);
    tFlexitime givingBack = flexiInit(0, 0);

    // Ask for flexi hours reduced
    puts("Enter flexi reduced:");
    getTimeFromUser(&flexiReduced);

    puts("Enter flexi gained:");
    getTimeFromUser(&flexiGained);

    // Debug
    printf("Reduced hours: ");
    flexiPrint(&flexiReduced);
    printf("Gained hours: ");
    flexiPrint(&flexiGained);
    // Debug end

    // Ask for how many full days left to work

    printf("Enter full days left to work: ");
    int workDaysLeft = fgeti() % 7 + 1;  // has to be at least 1
    printf("%d\n", workDaysLeft);
    
    // Do calculation
    seconds workSecondsLeft = flexiTimeToSeconds(&workDays);
    printf("workSeconds = %d | err = %d\n", workSecondsLeft, errno);
    workSecondsLeft *= workDaysLeft;
    printf("workSecondsLeft = %d | err = %d\n", workSecondsLeft, errno);

    seconds gainedSeconds = flexiTimeToSeconds(&flexiGained);
    seconds reducedSeconds = flexiTimeToSeconds(&flexiReduced);
    printf("gainedSeconds = %d | reducedSeconds = %d\n", gainedSeconds, reducedSeconds);
    seconds secondsToGiveBack = (workSecondsLeft - reducedSeconds) - gainedSeconds;
    printf("secondsToGiveBack = %d\n", secondsToGiveBack);

    char returnPrint[50] = "Work less: ";
    if (secondsToGiveBack < 0)
    {
        strncpy(returnPrint, "Work more: ", 50);
        secondsToGiveBack *= -1;
    }
    flexiSecondsToFlexitime(&givingBack, secondsToGiveBack);

    printf("Giving back over %d days: " , workDaysLeft);
    flexiPrint(&givingBack);

    printf("Here are your results: \n");

    return 0;
}