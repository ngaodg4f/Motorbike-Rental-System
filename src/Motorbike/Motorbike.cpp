#include "Motorbike.h"

using std::cout, std::string;

Motorbike::Motorbike(
        int bike_id, 
        int member_id,
        string model,
        string color, 
        string engine_size,
        string transmission_mode,  
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
    cout << YELLOW
         << std::left << std::setw(15) << model
         << std::left << std::setw(15) << color
         << std::left << std::setw(15) << engine_size
         << std::left << std::setw(20) << transmission_mode
         << std::left << std::setw(8) << year
         << std::left << std::setw(17) << license_plate
         << std::left << std::setw(15) << description << '\n'
         << RESET;
}

void Motorbike::add_rental(double point_per_day, double minimum_rating, Date* start, Date* end){
    this->point_per_day = point_per_day;
    this->minimum_rating = minimum_rating;
    this->start = start;
    this->end = end;
    
    this->status = "AVAILABLE";
}

void Motorbike::reset_condition(){
    this->status = "NOT_AVAILABLE";
    point_per_day = 0;
    minimum_rating = 0;
    start = nullptr;
    end = nullptr;
}

void Motorbike::add_renter_to_list(Member* renter){
    renter_list.push_back(renter);
}