#include "Day.h"
using std::cout;

Day::Day(int day, int month, int year)
: day(day), month(month), year(year){}

void Day::set_date(int day, int month, int year){
    this->day = day;
    this->month = month;
    this->year = year;
}

int Day::get_day() { return day; }

int Day::get_month() { return month; }

int Day::get_year() { return year; }

void Day::print_date(){
    cout << "Day: " 
        << std::setw(2) << std::setfill('0')<< day << "/" 
        << std::setw(2) << std::setfill('0')<< month << "/" 
        << std::setw(2) << std::setfill('0') << year << '\n';
}