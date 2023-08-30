#ifndef _ADMIN_H_
#define _ADMIN_H_

#include <iostream>
#include "User.h"

class Admin : public User{
    public:
        void list_vehicle() override;
};

#endif
