#include "Motorbike.h"
using std::string;


Motorbike::Motorbike(int motorbike_id, int made_year, string engine_size, string tranmission_mode, string color, string license_plate, string description, string model, string location):
    motorbike_id(motorbike_id),
    made_year(made_year),
    engine_size(engine_size),
    tranmission_mode(tranmission_mode),
    color(color),
    license_plate(license_plate),
    description(description),
    model(model),
    location(location)
    {}

/*setters & getters*/

void Motorbike::set_engine_size(string engine_size){
    this->engine_size = engine_size;
}

void Motorbike::set_color(string color){
    this->color = color;
}

void Motorbike::set_license_plate(string license_plate){
    this->license_plate = license_plate;
}

void Motorbike::set_description(string description){
    this->description = description;
}

void Motorbike::set_model(string model){
    this->model = model;
}

void Motorbike::set_location(string location){
    this->location = location;
}

int Motorbike::get_motorbike_id(){
    return motorbike_id;
}

int Motorbike::get_made_year(){
    return made_year;
}

string Motorbike::get_engine_size(){
    return engine_size;
}

string Motorbike::get_tranmission_mode(){
    return tranmission_mode;
}

string Motorbike::get_color(){
    return color;
}

string Motorbike::get_license_plate(){
    return license_plate;
}

string Motorbike::get_description(){
    return description;
}

string Motorbike::get_model(){
    return model;
}

string Motorbike::get_location(){
    return location;
}