#include "Admin.h"

using std::cout, std::string;

Admin::Admin(){}

std::unordered_map<string, int> Admin::code_generator(int value, int code_amount = 1) {
    string code {};
    srand(time(NULL));

    std::unordered_map<string, int> key_code; // key: "XXXX-XXXX-XXXX-XXXX" -> value: "value"
    string binding {"QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890"};

    for (int i {}; i < code_amount; ++i) {
        string code {};
        for (int j {1}; j < 20; ++j) {
            if (j % 5 == 0) {
                code += '-';
                continue;
            }
            code += binding[rand() % 62]; 
            
        }
        key_code.insert({code, value});
        // cout << code << '\n';
    }    
    // for (auto key : key_code) {
    //     cout << key.first << " : " << key.second << '\n';
    // }
    return key_code; 
    
}
