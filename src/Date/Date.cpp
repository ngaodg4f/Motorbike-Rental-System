#include "Date.h"
using std::cout, std::string;

Date::Date(){} //Default constructor

Date::Date(int day, int month, int year )
: day(day), month(month), year(year){} //Constructor

/* Setters & Getters */
void Date::set_date(int day, int month, int year){
    this->day = day;
    this->month = month;
    this->year = year;
}

int Date::get_day() { return day; }

int Date::get_month() { return month; }

int Date::get_year() { return year; }


string Date::to_string(){ //format day values when writing them to a file
    return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
}

void Date::print_date(){ //display a date
    cout << "Date: " 
        << std::setw(2) << std::setfill('0') << day << "/" 
        << std::setw(2) << std::setfill('0') << month << "/" 
        << std::setw(2) << std::setfill('0') << year << '\n';
}