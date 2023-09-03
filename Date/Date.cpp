#include "Date.h"
using std::cout;

Date::Date(int day = 0, int month = 0, int year = 0)
: day(day), month(month), year(year){}

void Date::set_date(int day, int month, int year){
    this->day = day;
    this->month = month;
    this->year = year;
}

int Date::get_day() { return day; }

int Date::get_month() { return month; }

int Date::get_year() { return year; }

void Date::print_date(){
    cout << "Date: " 
        << std::setw(2) << std::setfill('0') << day << "/" 
        << std::setw(2) << std::setfill('0') << month << "/" 
        << std::setw(2) << std::setfill('0') << year << '\n';
}