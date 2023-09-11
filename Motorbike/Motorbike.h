#ifndef MOTORBIKE_H
#define MOTORBIKE_H

#include "../Date/Date.h"
#include "../Review/Review.h"

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

        // Manage renter who used the bike
        // --> get the score in `review` to define `motorbike_score`
        // (renter rates the bike)
        std::vector <Member*> renter_list;
        double motorbike_score = 0;
        std::vector <Review*> renter_review;

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

        void add_renter_to_list(Member* renter);

        friend class System;
};

#endif