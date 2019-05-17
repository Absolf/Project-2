#ifndef __DATE_H_INCLUDED__
#define __DATE_H_INCLUDED__
#include "utils.h"
#include <time.h>
using namespace std;


class Date
{
private:
    unsigned short day;
    unsigned short month;
    unsigned int year;

public:
    //Construtors of the class objects Date
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
    void setDate(unsigned int year, unsigned int month, unsigned int day); //Set all the Date atributes individually
    void setDateString(string yearMonthDay); //Set all the Date atributes through a string

    // outhet methods */

    static string returnDate(Date date); //Displays the date in a string
    friend ostream &operator<<(ostream &out, const Date &date); //operator that displays the date in a nice order
};
bool isBissexto(int year); //Determines if the input year is a leap year or not
int daysMonth(int month, int year); //Retrives the number of days in the input month (takes into account leap years)
bool verifyDate(string date); //Verifies if the date given is valid or not (taking into account days in a month, leap years and current date)

#endif