#include "Member.h"
using std::cout, std::string;
/* 
    No Exception Handling 
    No Getter
*/
Member::Member(string username = " ", string password = " ")
: username(username), password(password) {}

Member::Member(
            int id,
            std::string fullname,
            std::string phone,
            string id_type,
            string id_number,
            std::string license_number,
            Date* expiry_date,
            double credit_point,
            std::string username,
            std::string password,
            int bike_id,
            string location,
            double renting_score): 
        id(id),
        fullname(fullname),
        phone(phone),
        id_type(id_type),
        id_number(id_number),
        license_number(license_number),
        expiry_date(expiry_date),
        credit_point(credit_point),
        username(username),
        password(password),
        bike_id(bike_id),
        location(location),
        renting_score(renting_score) {}

void Member::link_bike(Motorbike* bike){
    this->bike = bike;
    this->bike_id = bike->bike_id;
}

void Member::view_personal_info(){
    cout << YELLOW
         << std::left << std::setw(10) << id
         << std::left << std::setw(20) << fullname
         << std::left << std::setw(15) << phone
         << std::left << std::setw(15) << id_type
         << std::left << std::setw(15) << id_number
         << std::left << std::setw(15) << license_number
         << std::left << std::setw(15) << expiry_date->to_string()
         << std::left << std::setw(15) << credit_point
         << std::left << std::setw(15) << location << '\n'
         << RESET;
}

void Member::add_renter_to_list(Member* renter){
    renter_list.push_back(renter);
    bike->add_renter_to_list(renter);
}

void Member::get_new_request(Request* request){
    request_list.push_back( request );
}

void Member::view_request(){
    cout << YELLOW
         << std::left << std::setw(10) << "ID" 
         << std::left << std::setw(20) << "FULL_NAME" 
         << std::left << std::setw(15) << "CREDIT" 
         << std::left << std::setw(15) << "START_DATE"
         << std::left << std::setw(15) << "END_DATE"
         << std::left << std::setw(15) << "RATING" << '\n'
         << RESET;

    for(auto request : request_list){
        request->view_request();
    }
}

void Member::use_credit_point(double point){
    credit_point -= point;
}

void Member::earn_credit_point(double point){
    credit_point += point;
}
