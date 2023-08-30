#include "User.h"

using std::string;

/* 
    No Exception Handling 
    No Getter
*/

User::User(string username = "default", string password = "Abc@1234") {
    this->username = username;
    this->password = password;
}

User::~User() {

}

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

void User::set_id_type(string id_type) { 
    this->id_type = id_type;
}

void User::set_id(string id) {
    this->id = id;
}

void User::set_driver_license(string driver_license) {
    this->driver_license = driver_license;
}