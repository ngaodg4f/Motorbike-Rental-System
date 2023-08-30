#ifndef _MEMBER_H_
#define _MEMBER_H_

#include <iostream>
#include "User.h"

class Member : public User{
    public:
        void list_vehicle() override;
};

#endif