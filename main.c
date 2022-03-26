// Flexi hour calculator
//
// Can Caglar 26th March 2022
//
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

typedef struct tFlexitime
{
    int hours;
    int minutes;
} tFlexitime;

int fgeti()
{
    // char ret[50];
    // fgets(ret, 50, stdin);
    // ret[strcspn(ret, "\n")] = 0;  // clear \n

    // strtol()
    // getchar();
    return rand();
}

// Returns 0 if success, non-0 if error.
int getTimeFromUser(struct tm* retTime)
{
    printf("Enter HOURS: ");
    retTime->tm_hour = fgeti() % 24;
    printf("Enter MINUTES: ");
    retTime->tm_min = fgeti() % 60;
    return 0;
}

int main()
{
    // Prestart
    srand((unsigned)time(NULL));  // seed random
    // Prestart end

    puts("Welcome to flexicalc");

    struct tm flexiReduced = { 0 };
    struct tm flexiGained = { 0 };
    struct tm workDays = { .tm_hour = 7, .tm_min = 30};

    // Ask for flexi hours reduced
    puts("Enter flexi reduced:");
    getTimeFromUser(&flexiReduced);

    puts("Enter flexi gained:");
    getTimeFromUser(&flexiGained);

    // Debug
    char debug[200];
    strftime(debug, 200, "%H hours %M minutes", &flexiReduced);
    printf("Reduced hours: %s\n", debug);
    strftime(debug, 200, "%H hours %M minutes", &flexiGained);
    printf("Gained hours: %s\n", debug);
    // Debug end

    // Ask for how many full days left to work

    printf("Enter full days left to work: ");
    int workDaysLeft = fgeti() % 31;
    printf("%d\n", workDaysLeft);
    time_t workSecondsLeft = mktime(&(struct tm){.tm_hour =0,
                                                 .tm_sec = 25,
                                                 .tm_mday = 2,
                                                 .tm_wday = 0,
                                                 .tm_yday = 70,
                                                 .tm_mon = 0,
                                                 .tm_year = 70});
    printf("workSecondsLeft = %ld | err = %d\n", workSecondsLeft, errno);
    workSecondsLeft *= workDaysLeft;

    // Do calculation

    // time_t gainedSeconds = mktime(&flexiGained);
    // time_t reducedSeconds = mktime(&flexiReduced);
    // printf("gainedSeconds = %ld | reducedSeconds = %ld\n", gainedSeconds, reducedSeconds);
    // time_t secondsToGiveBack = (workSecondsLeft - reducedSeconds) - gainedSeconds;
    // printf("secondsToGiveBack = %ld\n", secondsToGiveBack);
    // struct tm* giveback = localtime(&secondsToGiveBack);
    // strftime(debug, 200, "Giving back: %H hours %M minutes", giveback);

    printf("Here are your results: \n");

    return 0;
}