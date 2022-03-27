#include "FlexiHours.h"
#include <stdio.h>
#include <assert.h>

void test_flxTimeToMin(flxhour testHour,
                      flxminute testMinute,
                      flxminute expectedMinute,
                      kResult expectedResult)
{
    flxFlexiHour testStruct = { 0 };
    assert(flxUpdate(&testStruct, testHour, testMinute) == expectedResult);
    assert(flxTimeToMin(&testStruct, &testMinute) == expectedResult);
    if (expectedResult == SUCCESS)
    {
        assert(testMinute == (flxminute)expectedMinute);
    }
}

void test_flxMinToTimeStruct(flxminute testMinute,
                             flxhour expectedHour,
                             flxminute expectedMinute,
                             kResult expectedResult)
{
    flxFlexiHour testStruct = { 0 };
    assert(flxMinToTimeStruct(testMinute, &testStruct) == expectedResult);
    if (expectedResult == SUCCESS)
    {
        assert(testStruct.hours == expectedHour);
        assert(testStruct.minutes == expectedMinute);
    }
}

void tests()
{
    puts("Running tests");

    flxFlexiHour time;
    flxFlexiHour manualTest;
    // Test uninitialised struct returns fail
    assert(flxprint(&time) == FAIL); // should fail, not initialised

    // Test flxUpdate
    assert(flxUpdate(&time, 0, -1) == FAIL);  // should fail, not initialised
    assert(flxUpdate(&time, 0, 80) == SUCCESS);  // should pass
    assert(flxprint(&time) == SUCCESS);
    assert(flxUpdate(&manualTest, 1, 20) == SUCCESS);  // should pass
    assert(flxIsInitialised(&time));    // should pass
    assert(flxIsInitialised(&manualTest)); // should pass
    assert(time.hours == manualTest.hours &&
        time.minutes == manualTest.minutes);  // 80 mins should be same as 1:20

    // Test flxTimeToMin
    test_flxTimeToMin(6, 253, 613, SUCCESS);
    test_flxTimeToMin(-6, 254, 612, FAIL);
    test_flxTimeToMin(6, -254, 612, FAIL);
    test_flxTimeToMin(0, 0, 0, SUCCESS);
    test_flxTimeToMin(10, 0, 600, SUCCESS);
    test_flxTimeToMin(0, 3423, 3423, SUCCESS);

    // Test flxMinToTime
    test_flxMinToTimeStruct(323, 5, 23, SUCCESS);
    test_flxMinToTimeStruct(-323, 5, 23, FAIL);
    test_flxMinToTimeStruct(0, 0, 0, SUCCESS);
    test_flxMinToTimeStruct(60, 1, 0, SUCCESS);
    test_flxMinToTimeStruct(59, 0, 59, SUCCESS);

    puts("All tests passed!");
}

int main()
{
    tests();
}