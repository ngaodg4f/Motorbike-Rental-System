#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include "User.h"

class Member : public User{
    public:
        void list_vehicle() override;
};

#endif