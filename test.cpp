#include <iostream>
#include <vector> 
#include <string>
#include "src/define.h"
using std::cout;

int main(){
    cout << GREEN
         << BOLD
         << "--- ADMIN DASHBOARD -------------------------------------\n"
         << "| [1] View all members                                  |\n"
         << "| [2] View all motorbikes                               |\n"
         << "| [3] Generate code                                     |\n"
         << "| [4] EXIT                                              |\n"
         << "---------------------------------------------------------\n"
         << RESET;

    cout << GREEN
         << BOLD
         << "~~~~~~~~~~~~~~~ WELCOME TO OUR COMMUNITY ~~~~~~~~~~~~~~~~\n"
         << "--- GUEST MENU ------------------------------------------\n"
         << "| [1] View all motorbikes                               |\n"
         << "| [2] Member registration                               |\n"
         << "| [3] Exit                                              |\n"
         << "---------------------------------------------------------\n"
         << RESET;
}