/*copies of the month_day and day_of_year functions from K&R chapter 5,
 * these have been edited according to exercise 5-8*/

#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pda);

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main()
{
    /*TODO; write tests to try to break the functions*/
    printf("%d\n", day_of_year(2012, 2, 4));
    return 0;
}


int day_of_year(int year, int month, int day)
{
    int i, leap;
    if(year < 1752 || month < 1 || month > 12)
    {
        return -1;/*clumsy error code*/
    }
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if(day > *(*(daytab + leap) + month))
    {
        return -1;
    }
    for(i = 1; i < month; i++)
    {
        day += *(*(daytab + leap)+i);
    }
    return day;
}

/*I got the 1752 from the solutions page, it has to do with the Gregorian 
 * calender. */
void month_day(int year, int yearday, int * pmonth, int * pday)
{
    int i, leap;
    if(year < 1752 || yearday < 1)
    {
        *pmonth = -1;/*Another clumsy error code*/
        *pday = -1;
        return;
    }

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if((!leap && yearday > 365) || (leap && yearday > 366))
    {
        *pmonth = -1;
        *pday = -1;
        return;
    }
    for(i = 1; yearday > *(*(daytab+leap)+i); i++)
    {
        yearday -= *(*(daytab+leap)+i);
    }
    *pmonth = i;
    *pday = yearday;
}


