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
        Member(std::string , std::string);

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

        int get_id();

        void set_id(int id);

        std::string get_fullname();

        void set_fullname(std::string fullname);

        std::string get_phone();

        void set_phone(std::string phone);

        std::string get_id_type();

        void set_id_type(std::string id_type);

        std::string get_id_number();

        void set_id_number(std::string id_number);

        std::string get_license_number();

        void set_license_number(std::string license_number);

        Time get_expiry_date();

        void set_expiry_date(Time expiry_date);

        int get_credit_point();

        void set_credit_point(int credit_point);

        std::string get_username();

        void set_username(std::string username);

        std::string get_password();

        void set_password(std::string password);

        int get_bike_id();
        
        void set_bike_id(int bike_id);
};

#endif