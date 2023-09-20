#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <unordered_map>
#include <time.h>

class Admin {
    public:
        Admin();

        std::unordered_map<std::string, int> code_generator(int value, int amount);

        friend class System;
};

#endif
