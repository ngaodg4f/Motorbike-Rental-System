#ifndef TIME_H
#define TIME_H
#include <iostream>
#include <iomanip>

class Time {
    private:
        int day;
        int month;
        int year;

        int hour {0};
        int minute {0};
        int second {0};

    public:
        Time();

        Time(int day, int month, int year);

        void set_date(int Time, int month, int year);

        void set_time(int hour, int minute, int year);

        int get_time();

        int get_day();

        int get_month();

        int get_year();

        void print_date();
};

#endif