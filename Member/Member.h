#ifndef MEMBER_H
#define MEMBER_H

#include "../Date/Date.h"
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

        friend class System;
};

#endif