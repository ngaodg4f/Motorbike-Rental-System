#ifndef MOTORBIKE_H
#define MOTORBIKE_H


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

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

        void add_owner(Member* owner);

        friend class System;
};

#endif