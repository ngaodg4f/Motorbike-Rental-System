#ifndef USER_H
#define USER_H

#include <iostream>
using std::cout, std::string;

class User {
    private:
        int user_id;
        string fullname {};
        string username {};
        string password;
        string phone;
        string idType;
        string id;
        string driver_license;
        // Date expiry_date; // wait for Date class
        // vehicle_list // wait for Motorbike class
        // int credit_point; // wait for uml
    public:
        User() = default;
        User(string username, string password);
        ~User();
        void set_fullname(string fullname);
        void set_username(string username);
        void set_password(string password);
        void set_phone(string phone);
        void set_idType(string id_type); 
        void set_id(string id);
        void set_driver_license(string driver_license);
        // void set_expiry_date(Date expiry_date); // wait for Date class
        virtual void list_vehicle() = 0;
};

#endif