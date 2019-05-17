#include "Date.h"
#pragma warning(disable : 4996) //Erro associated with localtime error

//Construtors of the class objects Date
Date::Date()
{
}

Date::Date(string date)
{
    setDateString(date);
}

Date::Date(unsigned short day, unsigned short month, unsigned year) : day(day), month(month), year(year)
{
}

/*********************************
 * GET Methods
 ********************************/
unsigned int Date::getYear() const //retrives Year from Date
{
    return year;
}
unsigned int Date::getMonth() const //retrives Month from Date
{
    return month;
}
unsigned int Date::getDay() const //retrives Day from Date
{
    return day;
}

/*********************************
 * SET Methods
 ********************************/
void Date::setYear(unsigned int year)
{
    this->year = year;
}
void Date::setMonth(unsigned int month)
{
    this->month = month;
}
void Date::setDay(unsigned int day)
{
    this->day = day;
}

//Set all the Date atributes individually
void Date::setDate(unsigned int year, unsigned int month, unsigned int day)
{
    setYear(year);
    setMonth(month);
    setDay(day);
}

//Set all the Date atributes through a string
void Date::setDateString(string linha)
{
    unsigned int year;
    unsigned short month;
    unsigned short day;
    bool dateValidation = verifyDate(linha);
    if (dateValidation)
    {
        linha = regex_replace(linha, regex("/"), " ");
        istringstream teste(linha);
        teste >> year >> month >> day;
        setDate(year, month, day);
    }
}

//Retrives the Date in a form of a string
string Date::getDateString()
{
    string year = to_string(getYear());
    string month = to_string(getMonth());
    string day = to_string(getDay());
    string oneLine = year + "/" + month + "/" + day; //Creates a string with all the atributes of Date
    Date date(oneLine);
    return returnDate(date);
}

//Determines if the input year is a leap year or not
bool isBissexto(int year)
{
    if (year % 4 == 0 && year % 100 != 0)
        return true;
    else if (year % 400 == 0)
        return true;
    else
        return false;
}

//Retrives the number of days in the input month (takes into account leap years)
int daysMonth(int month, int year)
{
    if (month == 2)
    {
        if (isBissexto(year) == true)
            return 29;
        else
            return 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    else
        return 31;
}

//Verifies if the date given is valid or not (taking into account days in a month, leap years and current date)
bool verifyDate(string date)
{
    unsigned int year;
    unsigned short month;
    unsigned short day;
    date = regex_replace(date, regex("/"), " "); //Transforms the date into a string
    istringstream teste(date);
    teste >> year >> month >> day;
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime); //Determines the current date
    bool isDate = false;
    int thisYear = aTime->tm_year + 1900;
    int limit = thisYear + 10;
    unsigned short maxDay = daysMonth(month, year);
    if((year >= (unsigned) thisYear) && (year < (unsigned) limit) && //Conditions for date validation
       (month <= 12 && month > 0) &&
       (day <= maxDay && day > 0))
    {
        isDate = true;
    }
    else
    {
        cout << "Date limits for year(" << thisYear << "-" << limit << ") month (1-12) day (1-" << maxDay << ")" << endl;
        isDate = false;
    }
    return isDate;
}

//Return the date in a form of a string
string Date::returnDate(Date date)
{
    stringstream ss;
    string date_output;
    if (date.getMonth() < 10 && date.getDay() < 10)
    {
        ss << date.getYear() << "/0" << date.getMonth() << "/0" << date.getDay();
        date_output = ss.str();
    }
    else if (date.getMonth() < 10 && date.getDay() >= 10)
    {
        ss << date.getYear() << "/0" << date.getMonth() << "/" << date.getDay();
        date_output = ss.str();
    }
    else if (date.getMonth() >= 10 && date.getDay() < 10)
    {
        ss << date.getYear() << "/" << date.getMonth() << "/0" << date.getDay();
        date_output = ss.str();
    }
    else
    {
        ss << date.getYear() << "/" << date.getMonth() << "/" << date.getDay();
        date_output = ss.str();
    }
    return date_output;
}
