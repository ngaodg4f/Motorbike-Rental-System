#include "Motorbike.h"
#define FILE_NAME "../Data/Motorbike.txt"

using std::cout, std::string;

Motorbike::Motorbike(
        int bike_id = 0, 
        string model = "",
        string color = "", 
        string engine_size = "",
        string tranmission_mode = "",  
        int year = 0, 
        string license_plate = "",
        string description = "")
    : bike_id(bike_id),
    model(model),
    color(color),
    engine_size(engine_size),
    transmission_mode(transmission_mode),
    year(year),
    license_plate(license_plate),
    description(description){}

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

void Motorbike::print_info(){
    cout << " + MOTORBIKE " << bike_id << " DETAIL" << '\n';
    cout << "ID: " << bike_id << '\n';
    cout << "Owner ID: " << member_id << '\n';
    cout << "Model: " << model << '\n';
    cout << "Color: " << color << '\n';
    cout << "Engine size: " << engine_size << '\n';
    cout << "Transmission mode: " << transmission_mode << '\n';
    cout << "Made in: " << year << '\n';
    cout << "Plate number: " << license_plate << '\n';
    cout << "Description: " << description << '\n';
}

int Motorbike::get_bike_id() { return bike_id; }

void Motorbike::set_bike_id(int bike_id) { this->bike_id = bike_id; }

int Motorbike::get_member_id() { return member_id; }

void Motorbike::set_member_id(int member_id) { this->member_id = member_id; }

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

Motorbike* parse (string data){
    if(data.empty() || data[0] == '#'){ return NULL; }

    std::stringstream ss { data };
    std::vector<string> tokens;
    string input;

    while(getline(ss, input, ',')){
        tokens.push_back(input);
    }

    return new Motorbike ( std::stoi(tokens.at(0)), 
                           std::stoi(tokens.at(1)),
                           tokens.at(2),
                           tokens.at(3),
                           tokens.at(4),
                           tokens.at(5),
                           std::stoi(tokens.at(6)),
                           tokens.at(7),
                           tokens.at(8) );
}

string serialize (Motorbike* bike){
    return std::to_string(bike->get_bike_id()) + ","
        + std::to_string(bike->get_member_id()) + ","
        + bike->get_model() + ","
        + bike->get_color() + ","
        + bike->get_engine_size() + ","
        + bike->get_transmission_mode() + ","
        + std::to_string(bike->get_year()) + ","
        + bike->get_license_plate() + ","
        + bike->get_description();
}

std::vector<Motorbike*> get_all_bike() {
    std::vector<Motorbike*> list;
    std::ifstream data_file (FILE_NAME);
    if(!data_file.is_open()){
        std::cerr << "Error: Unable to open file " << FILE_NAME << '\n';
        return list;
    }

    string line;
    while(getline(data_file, line)){
        Motorbike* bike = parse(line);
        if(bike){
            list.push_back( bike );
            }
        }
    return list;
}

int main(){
    std::vector<Motorbike*> list;
    list = get_all_bike();
    for(int i = 0; i < list.size(); i++){
        list.at(i)->print_info();
        delete list.at(i);
    }
}