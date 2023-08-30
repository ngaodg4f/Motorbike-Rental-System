#ifndef _USER_H_
#define _USER_H_

#include <iostream>

class User {
    private:
        int user_id;
        std::string fullname;
        std::string username;
        std::string password;
        std::string phone;
        std::string id_type;
        std::string id;
        std::string driver_license;
        // Date expiry_date; // wait for Date class
        // vehicle_list // wait for Motorbike class
        // int credit_point; // wait for uml
    public:
        User(std::string username, std::string password);
        ~User();
        void set_fullname(std::string fullname);
        void set_username(std::string username);
        void set_password(std::string password);
        void set_phone(std::string phone);
        void set_id_type(std::string id_type); 
        void set_id(std::string id);
        void set_driver_license(std::string driver_license);
        // void set_expiry_date(Date expiry_date); // wait for Date class
        virtual void list_vehicle() = 0;
};

#endif