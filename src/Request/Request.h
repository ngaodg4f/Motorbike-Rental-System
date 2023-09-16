#ifndef REQUEST_H
#define REQUEST_H

#include "../Member/Member.h"

#include <iostream>
#include <iomanip>
#include <string>
#include "../define.h"

class Request {
    private:
        Member* renter;

        Date* start;
        Date* end;

        std::string status { "WAITING" };

    public:
        Request();
        Request(Member* renter, Date* start, Date* end);

        void view_request();

        void get_accepted();

        friend class System;
        friend class Member;
};

# endif