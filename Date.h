#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "defs.h"

using namespace std;

class Date
{
private:
    unsigned short day;
    unsigned short month;
    unsigned int year;

public:
    Date();
    Date(string yearMonthDay); // yearMonthDay must be in format "yyyy/mm/dd"
    Date(unsigned short day, unsigned short month, unsigned year);
    // GET methods
    unsigned int getYear() const;
    unsigned int getMonth() const;
    unsigned int getDay() const;
    string getDateString(); // returns the date in format "yyyy/mm/dd"

    // SET methods
    void setYear(unsigned int year);
    void setMonth(unsigned int month);
    void setDay(unsigned int day);
    void setDate(unsigned int year, unsigned int month, unsigned int day);
    void setDateString(string yearMonthDay);

    // outhet methods */
    string returnDate(Date date); //returns the date in format "yyyy/mm/dd"
    friend ostream &operator<<(ostream &out, const Date &date);
};
