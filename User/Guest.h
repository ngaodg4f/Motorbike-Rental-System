#ifndef GUEST_H
#define GUEST_H

#include <iostream>
#include "User.h"

class Guest : public User{
    public:
        void list_vehicle() override;
};

#endif