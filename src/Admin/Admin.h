#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>

class Admin {
    public:
        Admin();

        std::string code_generator(int value, int code_amount);

        friend class System;
};

#endif
