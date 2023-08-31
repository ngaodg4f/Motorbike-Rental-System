#ifndef DAY_H
#define DAY_H
#include <iostream>
#include <iomanip>

class Day {
    private:
        int day;
        int month;
        int year;

    public:
        Day(int day, int month, int year);

        void set_date(int day, int month, int year);

        int get_day();

        int get_month();

        int get_year();

        void print_date();
};

#endif