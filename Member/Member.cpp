#include "Member.h"
using std::cout, std::string;
/* 
    No Exception Handling 
    No Getter
*/
Member::Member(string username = " ", string password = " ")
: username(username), password(password) {}

Member::Member(
            int id = 0,
            std::string fullname = "",
            std::string phone = "",
            string id_type = "",
            string id_number = "",
            std::string license_number = "",
            Time expiry_date,
            int credit_point = 20,
            int bike_id = 0,
            std::string username = "",
            std::string password = ""): 
        id(id),
        fullname(fullname),
        phone(phone),
        id_type(id_type),
        id_number(id_number),
        license_number(license_number),
        expiry_date(expiry_date),
        credit_point(credit_point),
        bike_id(bike_id),
        username(username),
        password(password) {}

void Member::set_fullname(string fullname) { this->fullname = fullname; }

void Member::set_username(string username) { this->username = username; }

void Member::set_password(string password) { this->password = password; }

void Member::set_phone(string phone) { this->phone = phone; }

void Member::set_id_type(string id_type) {  this->id_type = id_type; }

void Member::set_id_number(string id_number) { this->id_number = id_number; }

void Member::set_license_number(string license_number) { this->license_number = license_number; }