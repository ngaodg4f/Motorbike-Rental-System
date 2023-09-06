#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>

using std::cout, std::string;

string generate_code(){
    srand(time(0));
    string code {};

    for(int i = 0; i < 10; i++){
        int choice = (int)(rand() % 2);
        // 0 : number
        // 1 : char

        if(choice == 0){
            code += (char)(rand() % 10 + 48);
        } 
        if(choice == 1){
            code += (char)(rand() % 26 + 97);
        }
    }

    return code;
}

int main(){
    cout << generate_code() << '\n';
}