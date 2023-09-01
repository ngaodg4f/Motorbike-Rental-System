#include "Motorbike.h"
using std::string;

Motorbike::Motorbike(
        int bike_id = 0, 
        int member_id = 0,
        string model = "",
        string color = "", 
        string engine_size = "",
        string tranmission_mode = "",  
        int year = 0, 
        string license_plate = "",
        string description = "")
    : bike_id(bike_id),
    member_id(member_id),
    model(model),
    color(color),
    engine_size(engine_size),
    transmission_mode(transmission_mode),
    year(year),
    license_plate(license_plate),
    description(description){}

int Motorbike::get_bike_id() { return bike_id; }

void Motorbike::set_bike_id(int bike_id) { this->bike_id = bike_id; }

string Motorbike::get_model() { return model; }

void Motorbike::set_model(string model) { this->model = model; }

string Motorbike::get_color() { return color; }

void Motorbike::set_color(string color) { this->color = color; }

string Motorbike::get_engine_size() { return engine_size; }

void Motorbike::set_engine_size(string engine_size) { this->engine_size = engine_size; }

string Motorbike::get_transmission_mode() { return transmission_mode; }

void Motorbike::set_transmission_mode(string transmission_mode) { this->transmission_mode = transmission_mode; }

int Motorbike::get_year() { return year; }

void Motorbike::set_year(int year) { this->year = year; }

string Motorbike::get_license_plate() { return license_plate; }

void Motorbike::set_license_plate(string license_plate) { this->license_plate = license_plate; }

string Motorbike::get_description() { return description; }

void Motorbike::set_description(string description) { this->description = description; }

int Motorbike::get_member_id() { return member_id; }

void Motorbike::set_member_id(int member_id) { this->member_id = member_id; }
