#ifndef MEMBER_H
#define MEMBER_H

#include "../Date/Date.h"
#include "../Motorbike/Motorbike.h"

#include <iostream>
#include <vector>

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

        Motorbike* rented_bike;
        
        // Manage renter who rent bike
        // --> get the score in `review` to define renting_score
        // (owner rates the renters)
        std::vector<Member*> renter_list;
        double renting_score;
        Review* review_for_renter;

        std::vector<Member*> request_list;

    public:
        Member(std::string , std::string);

        // Member(
        //     int id,
        //     std::string fullname,
        //     std::string phone,
        //     std::string id_type,
        //     std::string id_number,
        //     std::string license_number,
        //     Date* expiry_date,
        //     double credit_point,
        //     std::string username,
        //     std::string password,
        //     int bike_id,
        //     std::string location);

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
            std::string location,
            double renting_score);

        void link_bike(Motorbike* bike);

        void view_personal_info();

        void add_renter_to_list(Member* renter);

        void get_request_from(Member* renter);

        friend class System;
};

#endif