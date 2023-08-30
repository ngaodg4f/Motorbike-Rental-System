#ifndef ADMIN_H
#define ADMIN_H

#include "../User/User.h"

class Admin : public User{
    public:
        void list_vehicle() override;
};

#endif
