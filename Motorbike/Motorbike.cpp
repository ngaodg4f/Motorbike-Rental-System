#include "Motorbike.h"

using std::cout, std::string;

Motorbike::Motorbike(
        int bike_id, 
        int member_id,
        string model,
        string color, 
        string engine_size,
        string tranmission_mode,  
        int year, 
        string license_plate,
        string description):
    bike_id(bike_id),
    member_id(member_id),
    model(model),
    color(color),
    engine_size(engine_size),
    transmission_mode(transmission_mode),
    year(year),
    license_plate(license_plate),
    description(description){}

