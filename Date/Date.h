#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <iomanip>

class Date {
    private:
        int day;
        int month;
        int year;

    public:
        Date();

        Date(int day, int month, int year);

        void set_date(int Date, int month, int year);

        int get_day();

        int get_month();

        int get_year();

        std::string to_string();

        void print_date();
};

#endif