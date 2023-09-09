#ifndef RENTING_H
#define RENTING_H

#include "../Member/Member.h"

#include <iostream>
#include <string>

class Renting {
    private:
        Member* renter;
        Motorbike* rent_bike;

    public:
        Renting(Member* renter, Motorbike* bike)
        : renter(renter), rent_bike(bike){}
};

# endif