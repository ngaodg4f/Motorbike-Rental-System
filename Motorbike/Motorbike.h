#ifndef MOTORBIKE_H
#define MOTORBIKE_H

#include <iostream>

class Motorbike {
    private:
        int motorbike_id;
        std::string model;
        std::string color;
        std::string engine_size;
        std::string tranmission_mode;
        int year;
        std::string license_plate;
        std::string description;

    public:
        Motorbike(
            int motorbike_id, 
            std::string model = "",
            std::string color = "", 
            std::string engine_size = "",
            std::string tranmission_mode = "",  
            int year = 0, 
            std::string license_plate = "", 
            std::string description = "");

    //setters & getters
        void set_engine_size(std::string);
        void set_color(std::string);
        void set_license_plate(std::string);
        void set_description(std::string);

        int get_motorbike_id();
        int get_year();
        std::string get_model();
        std::string get_engine_size();
        std::string get_tranmission_mode();
        std::string get_color();
        std::string get_license_plate();
        std::string get_description();

};

#endif /* MOTORBIKE_H */