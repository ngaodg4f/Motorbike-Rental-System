#ifndef MEMBER_H
#define MEMBER_H

#include "../Time/Time.h"
#include <iostream>

class Member {
    private:
        int id;
        std::string fullname;
        std::string phone;
        std::string id_type;
        std::string id_number;
        std::string license_number;
        Time expiry_date;
        int credit_point;
        std::string username;
        std::string password;
        int bike_id;

    public:
        Member(
            int id,
            std::string fullname,
            std::string phone,
            string id_type,
            string id_number,
            std::string license_number,
            Time expiry_date,
            int credit_point,
            int bike_id,
            std::string username,
            std::string password);

        Member(std::string , std::string);

        void set_fullname(std::string fullname);
        void set_username(std::string username);
        void set_password(std::string password);
        void set_phone(std::string phone);
        void set_id_type(std::string id_type); 
        void set_id_number(std::string id_number);
        void set_license_number(std::string license_number);
        // void set_expiry_date(Time expiry_date);
};

#endif