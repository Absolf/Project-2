#include "Date.h"

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
unsigned int Date::getYear()const{
    return year;
}
unsigned int Date::getMonth()const{
    return month;
}
unsigned int Date::getDay()const{
    return day;
}

/*********************************
 * SET Methods
 ********************************/
void Date::setYear(unsigned int year){
    this->year = year;
}
void Date::setMonth(unsigned int month){
    this->month = month;
}
void Date::setDay(unsigned int day){
    this->day = day;
}

void Date::setDate(unsigned int year, unsigned int month, unsigned int day){
    setYear(year);
    setMonth(month);
    setDay(day);
}

void Date::setDateString(string linha){
  unsigned int year;
  unsigned short month;
  unsigned short day;
  linha = regex_replace(linha, regex("/")," ");
  istringstream teste(linha);
  teste >> year >> month >> day;
  setDate(year,month,day);
}

//Verify if this is needed as i have return date function
string Date::getDateString(){
    string year = to_string(getYear());
    string month = to_string(getMonth());
    string day = to_string(getDay());
    string oneLine = year+"/"+month+"/"+day;
    Date date(oneLine);
    return returnDate(date);
}
string Date::returnDate(Date date){
    stringstream ss;
    string date_output;
    if (date.getMonth() < 10 && date.getDay() < 10){
        ss << date.getYear() << "/0" << date.getMonth()<< "/0" << date.getDay();
        date_output = ss.str();
    }else if(date.getMonth() <10 && date.getDay() > 10){
        ss << date.getYear() << "/0" << date.getMonth() << "/" << date.getDay();
        date_output = ss.str();
    }else if(date.getMonth() > 10 && date.getDay()< 10) {
        ss << date.getYear() << "/" << date.getMonth() << "/0" << date.getDay();
        date_output = ss.str();
    }else{
        ss << date.getYear() << "/" << date.getMonth() << "/" << date.getDay();
        date_output = ss.str();
    }
    return date_output;
}

/*********************************
 * Show Date
 ********************************/

// display a Date in a nice format
ostream &operator <<(ostream &out, const Date &date)
{
}
