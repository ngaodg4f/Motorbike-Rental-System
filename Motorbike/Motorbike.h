#ifndef MOTORBIKE_H
#define MOTORBIKE_H

// #include "../Member/Member.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

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

    public:
        Motorbike(
            int bike_id,
            std::string model,
            std::string color, 
            std::string engine_size,
            std::string transmission_mode,  
            int year, 
            std::string license_plate, 
            std::string description);

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

    void print_info();

    int get_bike_id();

    void set_bike_id(int bike_id);

    int get_member_id();

    void set_member_id(int member_id);

    std::string get_model();

    void set_model(std::string model);

    std::string get_color();

    void set_color(std::string color);

    std::string get_engine_size();

    void set_engine_size(std::string engine_size);

    std::string get_transmission_mode();

    void set_transmission_mode(std::string transmission_mode);

    int get_year();

    void set_year(int year);

    std::string get_license_plate();

    void set_license_plate(std::string license_plate);

    std::string get_description();

    void set_description(std::string description);
};

Motorbike* parse (std::string data);

std::string serialize (Motorbike* bike);

std::vector<Motorbike*> get_all_bike();

#endif