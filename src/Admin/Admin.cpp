#include "Admin.h"

using std::cout, std::string;

Admin::Admin(){} //Constructor

std::unordered_map<string, int> Admin::code_generator(int value, int code_amount = 1) { /* value = money, code_amount = the number of codes that admin wants to generate */
    string code {};
    srand(time(NULL));

    std::unordered_map<string, int> key_code; // key: "XXXX-XXXX-XXXX-XXXX" -> value: "value"
    string binding {"QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890"}; //each code will have some of these characters

    for (int i {}; i < code_amount; ++i) {
        string code {};
        /* 1 code has 4 group separated by "-", each group has 4 characters */
        for (int j {1}; j < 20; ++j) {
            if (j % 5 == 0) {
                code += '-';
                continue;
            }
            code += binding[rand() % 62]; // randomly take 16 characters from 62 characters
            
        }
        key_code.insert({code, value});
        // cout << code << '\n';
    }    
    for (auto key : key_code) {
        cout << key.first << '\n';
    }
    return key_code; 
    
}
