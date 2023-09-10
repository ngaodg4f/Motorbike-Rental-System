#include <iostream>
#include <regex>
#include <iomanip>
using std::cout, std::cin, std::string;

int main(){
    cout << "--- YOUR CURRENT STATUS ---" << '\n';
    cout << "Location: " << "SAIGON" << '\n';
    cout << "Points: " << "10.5"
         << std::right << std::setw(15)
         << "Rating: " << "0" << '\n';

    cout << std::left << std::setw(5) << "Start: " << "1/12/2023" << '\n';
    cout << std::left << std::setw(7) << "End: " << "1/1/2023" << '\n';

    return 0;
}