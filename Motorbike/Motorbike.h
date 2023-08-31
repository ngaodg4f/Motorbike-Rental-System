#ifndef MOTORBIKE_H
#define MOTORBIKE_H

#include <iostream>


class Motorbike {
    private:
        int motorbike_id;
        int made_year; //only year
        std::string engine_size; //follow a format
        std::string tranmission_mode;
        std::string color;
        std::string license_plate;
        std::string description;
        std::string model;
        std::string location;
    public:
        Motorbike(int motorbike_id, int made_year = 0, std::string engine_size = "", std::string tranmission_mode = "", std::string color = "", std::string license_plate = "", std::string description = "", std::string model = "", std::string location = "");

    //setters & getters
        void set_engine_size(std::string);
        void set_color(std::string);
        void set_license_plate(std::string);
        void set_description(std::string);
        void set_model(std::string);
        void set_location(std::string);

        int get_motorbike_id();
        int get_made_year();
        std::string get_engine_size();
        std::string get_tranmission_mode();
        std::string get_color();
        std::string get_license_plate();
        std::string get_description();
        std::string get_model();
        std::string get_location();
};

#endif /* MOTORBIKE_H */