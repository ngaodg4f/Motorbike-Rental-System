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
            int credit_point,
            std::string username,
            std::string password,
            int bike_id): 
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

int Member::get_id() { return id; }

void Member::set_id(int id) { this->id = id; }

std::string Member::get_fullname() { return fullname; }

void Member::set_fullname(std::string fullname) { this->fullname = fullname; }

std::string Member::get_phone() { return phone; }

void Member::set_phone(std::string phone) { this->phone = phone; }

std::string Member::get_id_type() { return id_type; }

void Member::set_id_type(std::string id_type) { this->id_type = id_type; }

std::string Member::get_id_number() { return id_number; }

void Member::set_id_number(std::string id_number) { this->id_number = id_number; }

std::string Member::get_license_number() { return license_number; }

void Member::set_license_number(std::string license_number) { this->license_number = license_number; }

Date* Member::get_expiry_date() { return expiry_date; }

void Member::set_expiry_date(Date* expiry_date) { this->expiry_date = expiry_date; }

int Member::get_credit_point() { return credit_point; }

void Member::set_credit_point(int credit_point) { this->credit_point = credit_point; }

std::string Member::get_username() { return username; }

void Member::set_username(std::string username) { this->username = username; }

std::string Member::get_password() { return password; }

void Member::set_password(std::string password) { this->password = password; }

int Member::get_bike_id() { return bike_id; }

void Member::set_bike_id(int bike_id) { this->bike_id = bike_id; }