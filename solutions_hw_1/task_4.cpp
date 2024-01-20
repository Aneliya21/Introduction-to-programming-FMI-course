#include <iostream>

const unsigned MIN = 1;

const unsigned YEAR_MIN_VALUE = 1600;
const unsigned YEAR_MAX_VALUE = 2100;

const unsigned LEAP_YEAR_COUNT_OF_DAYS = 366;
const unsigned NOT_LEAP_YEAR_COUNT_OF_DAYS = 365;

const unsigned FROM_JULIAN_TO_GRIGORIAN_CAL_YEAR = 1916;

const unsigned COUNT_OF_MONTHS_IN_A_YEAR = 12;

//MONTHS
const unsigned JAN = 1;
const unsigned FEB = 2;
const unsigned MAR = 3;
const unsigned APR = 4;
const unsigned MAY = 5;
const unsigned JUNE = 6;
const unsigned JUL = 7;
const unsigned AUG = 8;
const unsigned SEP = 9;
const unsigned OCT = 10;
const unsigned NOV = 11;
const unsigned DEC = 12;


const unsigned COUNT_OF_DAYS_IN_FEB_IN_LEAP_YEAR = 29;
const unsigned COUNT_OF_DAYS_IN_FEB_NOT_IN_LEAP_YEAR = 28;


bool areIntervalsCorrect(unsigned startYear, unsigned startMonth, unsigned startDay, unsigned endYear, unsigned endMonth, unsigned endDay) {
    return ((startYear < endYear) || 
        (startYear == endYear && startMonth < endMonth) ||
        (startYear == endYear && startMonth == endMonth && startDay <= endDay));
}

bool isLeapYear(unsigned year) {
    if (year <= 1916) {
        return year % 4 == 0;
    }
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

bool isLeapYearBasedOnCountOfDaysSinceBeg(unsigned& countOfDaysSinceBeg, unsigned year) {
    if (countOfDaysSinceBeg <= 115506) {
        return year % 4 == 0;
    }
}

unsigned countOfDaysInMonth(unsigned year, unsigned month) {
    switch (month) {
    case JAN:
    case MAR:
    case MAY:
    case JUL:
    case AUG:
    case OCT:
    case DEC:
        return 31; break; //count of days
    case FEB:
        return isLeapYear(year) ? COUNT_OF_DAYS_IN_FEB_IN_LEAP_YEAR : COUNT_OF_DAYS_IN_FEB_NOT_IN_LEAP_YEAR; break;
    case APR:
    case JUNE:
    case SEP:
    case NOV:
        return 30; break; //count of days
    }
}

bool isValidYear(unsigned year) {
    return (year >= YEAR_MIN_VALUE && year <= YEAR_MAX_VALUE);
}

bool isValidMonth(unsigned month) {
    return (month >= MIN && month <= COUNT_OF_MONTHS_IN_A_YEAR);
}

bool isValidDay(unsigned year, unsigned month, unsigned day) {
    return (day >= MIN && day <= countOfDaysInMonth(year, month));
}

bool isValidN(unsigned n) {
    return n >= MIN && n <= NOT_LEAP_YEAR_COUNT_OF_DAYS;
}

bool isExistingDate(unsigned year, unsigned month, unsigned day) {
    if (year == FROM_JULIAN_TO_GRIGORIAN_CAL_YEAR && month == APR) {
        return day > 13;    //dates from 1.4.1916 until 13.4.1916 do NOT exist
    }
    return true;
}

bool isValidDate(unsigned year, unsigned month, unsigned day) {
    return isExistingDate(year, month, day) && isValidYear(year) && isValidMonth(month) && isValidDay(year, month, day);
}

unsigned countOfDaysFromStartDateToCurrDate(unsigned currYear, unsigned currMonth, unsigned currDay) {
    unsigned countOfDays = 0; 
    if (currYear != YEAR_MIN_VALUE) {
        for (unsigned i = YEAR_MIN_VALUE; i < currYear; i++) {
            if (isLeapYear(i)) {
                countOfDays += LEAP_YEAR_COUNT_OF_DAYS;
            }
            else {
                countOfDays += NOT_LEAP_YEAR_COUNT_OF_DAYS;
            }
        }
    }
    if (currMonth != 1) {
        for (unsigned i = 1; i < currMonth; i++) {
            countOfDays += countOfDaysInMonth(currYear, i);
        }
    }
    countOfDays += (currDay - 1);
    countOfDays -= 3;
    return countOfDays;
}

unsigned calcYearAfterDays(unsigned& countOfDays) {
    unsigned currentYear = YEAR_MIN_VALUE;
    while (countOfDays > 0) {
        int daysInCurrentYear = isLeapYear(currentYear) ? LEAP_YEAR_COUNT_OF_DAYS : NOT_LEAP_YEAR_COUNT_OF_DAYS;

        if (countOfDays > daysInCurrentYear) {
            countOfDays -= daysInCurrentYear;
            currentYear++;
        }
        else {
            break;
        }
    }
    return currentYear;
}

unsigned calcMonthAfterDays(unsigned& year, unsigned& countOfDays) {
    unsigned currentMonth = MIN;
    if (countOfDays < countOfDaysInMonth(year, currentMonth)) {
        return currentMonth;
    }
    else {
        while (countOfDays >= countOfDaysInMonth(year, currentMonth)) { //63 //63-31=32=>2 =>32-31=1=>3
            countOfDays -= countOfDaysInMonth(year, currentMonth);
            currentMonth++;
        }
    }
    countOfDays += 4;
    if (currentMonth == 13) { //invalid month
        year++;
        currentMonth--;
    }
    return currentMonth;
}

void printInterval(unsigned& year, unsigned& month, unsigned& day, unsigned n) {
    if (!isExistingDate(year, month, day)) {
        day = 14;  //dates from 1.4.1916 until 13.4.1916 do NOT exist
    }
    
    unsigned currYear = year, currMonth = month, currDay = day;
    unsigned days = countOfDaysFromStartDateToCurrDate(year, month, day);
    days += n-2;
    year = calcYearAfterDays(days);
    month = calcMonthAfterDays(year, days);
    day = days;

    if (year > currYear) {
        days = countOfDaysFromStartDateToCurrDate(year, month, day);
        days -= n - 2;
        days += n;
        year = calcYearAfterDays(days);
        month = calcMonthAfterDays(year, days);
        day = days;
    }
    
    if (!isExistingDate(year, month, day)) {
        day = 15;  //dates from 1.4.1916 until 13.4.1916 do NOT exist
    }
    if (!isValidDay(year, month, day)) {
        unsigned diff = day - countOfDaysInMonth(year, month);
        day = diff;
        month++;
    }
    std::cout << currYear << "-" << currMonth << "-" << currDay << " - ";
    std::cout << year << "-" << month << "-" << day;
    std::cout << std::endl;
}

unsigned incrementWithN(unsigned year, unsigned month, unsigned day, unsigned n) {
    if (!isExistingDate(year, month, day)) {
        day = 14;  //dates from 1.4.1916 until 13.4.1916 do NOT exist
    }
    unsigned days = countOfDaysFromStartDateToCurrDate(year, month, day);
    days += n - 2;
    unsigned currYear = calcYearAfterDays(days);
    unsigned currMonth = calcMonthAfterDays(year, days);
    unsigned currDay = days;

    if (year > currYear) {
        days = countOfDaysFromStartDateToCurrDate(year, month, day);
        days -= n - 2;
        days += n;
        year = calcYearAfterDays(days);
        month = calcMonthAfterDays(year, days);
        day = days;
    }

    if (!isExistingDate(currYear, currMonth, currDay)) {
        currDay = 14;  //dates from 1.4.1916 until 13.4.1916 do NOT exist
    }
    if (!isValidDay(year, month, day)) {
        unsigned diff = day - countOfDaysInMonth(year, month);
        day = diff;
        month++;
    }
    days = countOfDaysFromStartDateToCurrDate(currYear, currMonth, currDay);
    return days;
}

void goToNextDay(unsigned& year, unsigned& month, unsigned& day) {
    unsigned days = countOfDaysFromStartDateToCurrDate(year, month, day);
    days+=1;
    year = calcYearAfterDays(days);
    month = calcMonthAfterDays(year, days);
    day = days - 1;
}

void printAllIntervals(unsigned startYear, unsigned startMonth, unsigned startDay, unsigned endYear, unsigned endMonth, unsigned endDay, unsigned n) {
    if (isValidDate(startYear, startMonth, startDay) && isValidDate(endYear, endMonth, endDay)) {
        if (areIntervalsCorrect(startYear, startMonth, startDay, endYear, endMonth, endDay)) {
            if (isValidN(n)) {
                unsigned currStartYear = startYear,
                    currStartMonth = startMonth,
                    currStartDay = startDay;

                unsigned startDaysCount = countOfDaysFromStartDateToCurrDate(currStartYear, currStartMonth, currStartDay);
                unsigned endDaysCount = countOfDaysFromStartDateToCurrDate(endYear, endMonth, endDay);

                while (startDaysCount <= endDaysCount) {

                    if (incrementWithN(currStartYear, currStartMonth, currStartDay, n) > endDaysCount) {

                        unsigned diff = endDaysCount - countOfDaysFromStartDateToCurrDate(currStartYear, currStartMonth, currStartDay);
                        printInterval(currStartYear, currStartMonth, currStartDay, diff + 1);
                        break;
                    }

                    printInterval(currStartYear, currStartMonth, currStartDay, n);
                    goToNextDay(currStartYear, currStartMonth, currStartDay);
                    startDaysCount = countOfDaysFromStartDateToCurrDate(currStartYear, currStartMonth, currStartDay);
                }
            }
            else {
                std::cout << "Invalid n!";
                std::cout << std::endl;
            }
        }
        else {
            std::cout << "Invalid intervals!";
            std::cout << std::endl;
        }
    }
    else {
        std::cout << "Ivalid dates!";
        std::cout << std::endl;
    }
}

int main()
{
    unsigned Syear, Smonth, Sday, Eyear, Emonth, Eday, n;
    std::cin >> Syear >> Smonth >> Sday >> Eyear >> Emonth >> Eday >> n;
    printAllIntervals(Syear, Smonth, Sday, Eyear, Emonth, Eday, n);
}
