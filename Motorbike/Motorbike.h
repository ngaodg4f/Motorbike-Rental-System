#ifndef MOTORBIKE_H
#define MOTORBIKE_H

#include "../Date/Date.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>

class Member;

class Motorbike {
    private:
        int bike_id;
        int member_id;
        std::string model;
        std::string color;
        std::string engine_size;
        std::string transmission_mode;
        int year;
        std::string license_plate;
        std::string description; 

        Member* owner;

        std::string status { "NOT_AVAILABLE "};

        Date* start = nullptr;
        Date* end = nullptr;
        double point_per_day;
        double minimum_rating;

    public:
        Motorbike(
            int bike_id,
            int member_id,
            std::string model,
            std::string color, 
            std::string engine_size,
            std::string transmission_mode,  
            int year, 
            std::string license_plate, 
            std::string description);

        void link_owner(Member* owner);

        void view_bike_info();

        void add_rental(double point_per_day, double minimum_rating, Date* start, Date* end);

        void reset_condition();

        friend class System;
};

#endif