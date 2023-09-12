#ifndef REQUEST_H
#define REQUEST_H

#include "../Member/Member.h"

#include <iostream>
#include <string>

class Request {
    private:
        Member* renter;

        Date* start;
        Date* end;

    public:
        Request(Member* renter, Date* start, Date* end);

        friend class System;
        friend class Member;
};

# endif