#include <iostream>
#include "src/define.h"
using std::cout, std::string;
#define RESET "\033[0m"
#define RED "\033[031m"

int main()
{

    cout << GREEN
         << BOLD
         << "----------------------- LOGIN AS ------------------------\n"
         << "| 1. Guest\t2. Member\t3. Admin\t4. Exit |\n"
         << "---------------------------------------------------------\n";
    cout << CYAN
         << "---------------- |WELCOME TO COMMUNITY| -----------------\n"
         << "                       GUEST MENU                        \n" << RESET;
    cout << "Hello" << '\n';
    cout  << RESET;
}