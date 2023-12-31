#ifndef MEMBER_H
#define MEMBER_H

#include "../Date/Date.h"
#include "../Motorbike/Motorbike.h"
#include "../Request/Request.h"
#include "../define.h"

#include <iostream>
#include <vector>

class Request;

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

        Motorbike* bike = nullptr;

        Motorbike* rented_bike = nullptr;

        // Manage renter who rent bike
        // --> get the score in `review` to define renting_score
        // (owner rates the renters)
        std::vector<Member*> renter_list; //store data of renters
        double renting_score = 0;
        std::vector <Review*> owner_review; 

        std::vector <Request*> request_list; //store requests for the motorbikes

    public:

    /* Constructors */
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

        void add_request(Request* request);

        void view_request();

        void use_credit_point(double point);

        void earn_credit_point(double point);

        void add_review(Review* review);

        double get_new_renting_score(double score);

        void reset_review();

        friend class System;
        friend class Admin;
        friend class Request;
        friend class Motorbike;
};

#endif