#include "Member.h"
using std::cout, std::string;
/* 
    No Exception Handling 
    No Getter
*/

Member::Member(string username = " ", string password = " ") //usually used for login task
: username(username), password(password) {}

Member::Member(
            int id,
            string fullname,
            string phone,
            string id_type,
            string id_number,
            string license_number,
            Date* expiry_date,
            double credit_point,
            string username,
            string password,
            int bike_id,
            string location): 
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
        location(location) {}

Member::Member(
            int id,
            string fullname,
            string phone,
            string id_type,
            string id_number,
            string license_number,
            Date* expiry_date,
            double credit_point,
            string username,
            string password,
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
}

void Member::view_personal_info(){ //A user can view his/her account info
    cout << YELLOW
         << std::left << std::setw(10) << id
         << std::left << std::setw(20) << fullname
         << std::left << std::setw(15) << phone
         << std::left << std::setw(15) << id_type
         << std::left << std::setw(15) << id_number
         << std::left << std::setw(15) << license_number
         << std::left << std::setw(15) << expiry_date->to_string()
         << std::left << std::setw(15) << credit_point
         << std::left << std::setw(15) << location
         << std::left << std::setw(15) << renting_score << '\n'

         << RESET;
}

void Member::add_renter_to_list(Member* renter){
    renter_list.push_back(renter);
    bike->add_renter_to_list(renter);
}

void Member::add_request(Request* request){
    request_list.push_back( request );
}

void Member::view_request(){ //An owner can view the requests for his/her motorbikes
    cout << YELLOW
         << std::left << std::setw(15) << "CHOICE"
         << std::left << std::setw(15) << "RENTER_ID" 
         << std::left << std::setw(20) << "FULL_NAME" 
         << std::left << std::setw(15) << "CREDIT" 
         << std::left << std::setw(15) << "START_DATE"
         << std::left << std::setw(15) << "END_DATE"
         << std::left << std::setw(15) << "RATING"
         << std::left << std::setw(15) << "STATUS" << '\n'
         << RESET;

    for(auto request : request_list){
        request->view_request();
    }
}

void Member::use_credit_point(double point){ //use the num of points for renting 
    credit_point -= point;
}

void Member::earn_credit_point(double point){ 
    credit_point += point;
}

void Member::add_review(Review* review){ 
    owner_review.push_back(review);
    renting_score = get_new_renting_score(review->score);
}

double Member::get_new_renting_score(double score){
    return (renting_score * (owner_review.size() - 1) + score ) / owner_review.size();
}

void Member::reset_review(){
    owner_review.clear();
    renting_score = 0;
}
