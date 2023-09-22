#include "Motorbike.h"

using std::cout, std::string;

Motorbike::Motorbike( //Constructor
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

void Motorbike::set_bike_id(int id) {
    this->bike_id = id;
}

int Motorbike::get_bike_id() {
    return this->bike_id;
}

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
         << std::left << std::setw(10) << motorbike_score
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

void Motorbike::add_review(Review* review){
    renter_review.push_back(review);
    motorbike_score = get_new_bike_score( review->score );
}

double Motorbike::get_new_bike_score(double score){
    return (motorbike_score * (renter_review.size() - 1) + score) / renter_review.size();
}

void Motorbike::reset_review(){
    renter_review.clear();
    motorbike_score = 0;
}