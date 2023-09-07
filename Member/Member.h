#ifndef MEMBER_H
#define MEMBER_H

#include "../Date/Date.h"
#include "../Motorbike/Motorbike.h"

#include <iostream>

class Member {
    private:
        int id;
        std::string fullname;
        std::string phone;
        std::string id_type;
        std::string id_number;
        std::string license_number;
        Date* expiry_date;
        double credit_point;
        std::string username;
        std::string password;
        int bike_id;
        std::string location;

        Motorbike* bike;

    public:
        Member(std::string , std::string);

        Member(
            int id,
            std::string fullname,
            std::string phone,
            std::string id_type,
            std::string id_number,
            std::string license_number,
            Date* expiry_date,
            double credit_point,
            std::string username,
            std::string password,
            int bike_id,
            std::string location);

        void link_bike(Motorbike* bike);

        void view_personal_info();

        friend class System;
};

#endif