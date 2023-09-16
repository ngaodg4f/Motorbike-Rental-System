#include "Admin.h"

#include <cstdlib>
#include <unordered_map>
#include <time.h>

using std::cout, std::string;

Admin::Admin(){}

string Admin::code_generator(int value, int code_amount = 1) {
    srand(time(0));

    std::unordered_map<string, int> key_code; // key: "XXXX-XXXX-XXXX-XXXX" -> value: "value"
    string binding {"QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890"};

    for (int i {}; i < code_amount; ++i) {
        string code {};
        for (int j {}; j < 19; ++j) {
            if (j % 4 == 0) {
                code += '-';
                continue;
            }
            code += binding[rand() % 63]; 
        }
        key_code.insert({code, value});
    }    
}
