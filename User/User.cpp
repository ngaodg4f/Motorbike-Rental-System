#include "User.h"
using std::cout, std::string;
/* 
    No Exception Handling 
    No Getter
*/

User::User(string username, string password)
: username(username), password(password) {}

User::~User() {}

void User::set_fullname(string fullname) {
    this->fullname = fullname;
}

void User::set_username(string username) {
    this->username = username;
}

void User::set_password(string password) {
    this->password = password;
}

void User::set_phone(string phone) {
    this->phone = phone;
}

void User::set_idType(string idType) { 
    this->idType = idType;
}

void User::set_id(string id) {
    this->id = id;
}

void User::set_driver_license(string driver_license) {
    this->driver_license = driver_license;
}