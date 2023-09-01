#include <iostream>
#include <string>

using std::cout, std::string;

class Motorbike {
    private:
        int motorbike_id;
        string model;
        string color;
        string engine_size;
        string tranmission_mode;
        int year;
        string license_plate;
        string description;

    public: 
        Motorbike(
            int motorbike_id = 0, 
            string model = "",
            string color = "", 
            string engine_size = "",
            string tranmission_mode = "",  
            int year = 0, 
            string license_plate = "", 
            string description = "")
        : motorbike_id(motorbike_id),
        model(model),
        color(color),
        engine_size(engine_size),
        tranmission_mode(tranmission_mode),
        year(year),
        license_plate(license_plate),
        description(description){
            // cout << "Motorbike " << motorbike_id << " was made" << '\n';
        }

        void print(){
            cout << "Motorbike " << motorbike_id << " was made" << '\n';
        }

        int get_motorbike_id() { return motorbike_id; }

        int get_year() { return year; }

        string get_model() { return model; }

        string get_engine_size() { return engine_size; }

        string get_tranmission_mode() {return tranmission_mode; }

        string get_color() {return color; }

        string get_license_plate() { return license_plate;}

        string get_description() {return description; }
};

#include <sstream>
#include <vector>
#include <map>
Motorbike* parse (string data){
    if(data.empty()){
        return NULL;
    }
    std::stringstream ss { data };
    std::vector<string> i;
    string input;

    while(getline(ss, input, ',')){
        i.push_back(input);
    }
    // Motorbike bike (std::stoi(i.at(0)), i.at(1), i.at(2), i.at(3), i.at(4), std::stoi(i.at(5)), i.at(6), i.at(7));
    return new Motorbike (std::stoi(i.at(0)), i.at(1), i.at(2), i.at(3), i.at(4), std::stoi(i.at(5)), i.at(6), i.at(7));
}

string serialize (Motorbike bike){
    return std::to_string(bike.get_motorbike_id()) + ","
        + bike.get_model() + ","
        + bike.get_color() + ","
        + bike.get_engine_size() + ","
        + bike.get_tranmission_mode() + ","
        + std::to_string(bike.get_year()) + ","
        + bike.get_license_plate() + ","
        + bike.get_description();
}

#include <fstream>

void getAllBike(){
    std::vector<Motorbike*> list {};
    std::ifstream file ("test.txt");
    if(!file.is_open()){
        std::cerr << "Error when opening files!" << '\n';
        return;
    }

    string line;
    while (getline(file, line)) {
        // list.push_back( parse(line) );     
        if(parse(line)){
            parse(line)->print();
        }
    }
    // cout << list.size();
    // return list;
}

int main(){
    // std::vector<Motorbike*> list;
    // list = getAllBike();
    // getAllBike();
    Motorbike bike;
    // cout << list.empty() << '\n';
    
    // if (!list.empty()) {
    //     list.at(0).print();
    // } else {
    //     std::cout << "The list of motorbikes is empty." << std::endl;
    // }
}