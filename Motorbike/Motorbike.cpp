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

void Motorbike::link_owner(Member* owner){
    this->owner = owner;
}

void Motorbike::view_bike_info(){
    cout << "----- YOUR BIKE ------" << '\n';
    cout << std::left << std::setw(10) << "MODEL" 
         << std::left << std::setw(20) << "COLOR" 
         << std::left << std::setw(16) << "ENGINE_SIZE" 
         << std::left << std::setw(15) << "TRANSMISSION_MODE"
         << std::left << std::setw(15) << "YEAR"
         << std::left << std::setw(15) << "LICENSE_PLATE"
         << std::left << std::setw(15) << "DESCRIPTION" << '\n';

    cout << std::left << std::setw(10) << model
         << std::left << std::setw(20) << color
         << std::left << std::setw(16) << engine_size
         << std::left << std::setw(15) << transmission_mode
         << std::left << std::setw(15) << year
         << std::left << std::setw(15) << license_plate
         << std::left << std::setw(15) << description << '\n';
}
