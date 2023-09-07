#include <iostream>
#include <regex>
using std::cout, std::cin, std::string;

int main(){
    string input;
    getline(cin, input);
    std::regex reg { "^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$" };
    if(std::regex_match(input, reg)){
        cout << "yes" << '\n';
    } else {
        cout << "no" << '\n';
    }

    return 0;
}