#ifndef REQUEST_H
#define REQUEST_H

#include "../Member/Member.h"

#include <iostream>
#include <iomanip>
#include <string>
#include "../define.h"

class Request {
    private:
        int request_id;
        Member* renter;

        Date* start;
        Date* end;

        std::string status;

    public:
        Request(Member* renter, Date* start, Date* end);
        Request(Member* renter, Date* start, Date* end, std::string status);

        void set_request_id(int id);

        void view_request();

        void get_accepted();

        friend class System;
        friend class Member;
};

# endif