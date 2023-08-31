#include "Member.h"
using std::cout, std::string;
/* 
    No Exception Handling 
    No Getter
*/

Member::Member(string username, string password)
: username(username), password(password) {}

Member::~Member() {}

void Member::set_fullname(string fullname) {
    this->fullname = fullname;
}

void Member::set_username(string username) {
    this->username = username;
}

void Member::set_password(string password) {
    this->password = password;
}

void Member::set_phone(string phone) {
    this->phone = phone;
}

void Member::set_idType(string idType) { 
    this->idType = idType;
}

void Member::set_id(string id) {
    this->id = id;
}

void Member::set_driver_license(string driver_license) {
    this->driver_license = driver_license;
}