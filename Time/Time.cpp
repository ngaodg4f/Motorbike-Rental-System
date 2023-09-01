#include "Time.h"
using std::cout;

Time::Time() = default;

Time::Time(int day = 0, int month = 0, int year = 0)
: day(day), month(month), year(year){}

void Time::set_date(int day, int month, int year){
    this->day = day;
    this->month = month;
    this->year = year;
}

void Time::set_time(int hour, int minute, int second){
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}

int Time::get_time() { return (hour * 3600 + minute * 60 + second); }

int Time::get_day() { return day; }

int Time::get_month() { return month; }

int Time::get_year() { return year; }

void Time::print_date(){
    cout << "Date: " 
        << std::setw(2) << std::setfill('0') << day << "/" 
        << std::setw(2) << std::setfill('0') << month << "/" 
        << std::setw(2) << std::setfill('0') << year << '\n';

    cout << "Time: " 
        << std::setw(2) << std::setfill('0') << hour << ":" 
        << std::setw(2) << std::setfill('0') << minute << ":" 
        << std::setw(2) << std::setfill('0') << second << '\n';
}