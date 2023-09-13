#ifndef REQUEST_H
#define REQUEST_H

#include "../Member/Member.h"

#include <iostream>
#include <iomanip>
#include <string>

class Request {
    private:
        Member* renter;

        Date* start;
        Date* end;

        std::string status { "DECLINED" };

    public:
        Request(Member* renter, Date* start, Date* end);

        void view_request();

        friend class System;
        friend class Member;
};

# endif