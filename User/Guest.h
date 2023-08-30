#ifndef _GUEST_H_
#define _GUEST_H_

#include <iostream>
#include "User.h"

class Guest : public User{
    public:
        void list_vehicle() override;
};

#endif