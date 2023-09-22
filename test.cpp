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
         << "Welcome, tung!" << '\n'
         << "--- MEMBER MENU -----------------------------------------\n"
         << "| [1] View personal details                             |\n"
         << "| [2] View your motorbike                               |\n"
         << "| [3] Add a new motorbike                               |\n"
         << "| [4] List bike for renting                             |\n"
         << "| [5] Un-List bike for rental                           |\n"
         << "| [6] Request renting a bike                            |\n"
         << "| [7] View requests from others                         |\n"
         << "| [8] Top up                                            |\n"
         << "| [9] Log out                                           |\n"
         << "---------------------------------------------------------\n"
         << RESET;

     cout << BLUE
         << BOLD
         << "---------------------------------------------------------\n"
         << "|                 UN-LIST SUCCESSFULLY                  |\n"
         << "---------------------------------------------------------\n"
         << RESET;
}