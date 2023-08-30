#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include "User.h"

class Admin : public User{
    public:
        void list_vehicle() override;
};

#endif
