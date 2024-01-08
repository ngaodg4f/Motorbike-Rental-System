#include <iostream>
#include <cstdlib>
#include "./System/System.h"

class System;

int main(){
    System sys;
    system("clear");
    sys.input_data();
    sys.welcome_screen();
    // Date *day1 = new Date {28,2,2000};
    // Date *day2 = new Date {5,3,2000};
    // std::cout << sys.count_day(day1, day2);
    return 0;
}

//input `make` in terminal