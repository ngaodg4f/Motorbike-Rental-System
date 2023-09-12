#include <iostream>

#include "./System/System.h"

int main(){
    System sys;
    sys.welcome_screen();

    return 0;
}

// g++ ./Motorbike/Motorbike.cpp ./Member/Member.cpp ./Date/Date.cpp ./Review/Review.cpp ./Admin/Admin.cpp ./Request/Request.cpp ./System/System.cpp main.cpp -o a.out