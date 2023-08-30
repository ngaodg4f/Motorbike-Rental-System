#ifndef MEMBER_H
#define MEMBER_H

#include "User.h"

class Member : public User{
    public:
        void list_vehicle() override;
};

#endif