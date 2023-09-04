#include <iostream>
#include <regex>
#include <algorithm>
using std::cout, std::cin, std::string;

string trim(string& str){
    string new_string;
    for(auto ch : str){
        if(ch != ' '){
            new_string += ch;
        }
    }

    return new_string;
}

bool validate_fullname(string& str){
    if(str.empty()){
        cout << "`Full name` can't be empty" << '\n';
        return false;
    }
    std::regex reg { "^[a-zA-Z0-9]{5,20}$" };
    string trim_string = trim(str);

    if(!std::regex_match(trim_string, reg)){
        cout << "`Full name` must contain 8 - 20 characters with no special characters" << '\n';
        return false;
    }

    return true;
}

bool validate_phone(string& str){
    if(str.empty()){
        cout << "`Phone` can't be empty" << '\n';
        return false;
    }

    std::regex reg1 { "^(0|84)[0-9]{9}$" };
    std::regex reg2 { "^(84)[0-9]{9}$" };
    string trim_string = trim(str);
  
    if(!std::regex_match(trim_string, reg1)){
        cout << "`Phone` must contain 10 numbers with no special character" << '\n';
        cout << "Either start with 0 or 84" << '\n';
        return false;
    }

    return true;
}

bool validate_id_type(string& str){
    if(str.empty()){
        cout << "`ID TYPE` can't be empty." << '\n';
        return false;
    }

    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    if(str != "id" && str != "license"){
        cout << "Input with wrong format. `Id` or `License` is available." << '\n';
        return false;
    }

    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return true;
}

bool validate_id_license_number(string& str){
    if(str.empty()){
        cout << "`Number` is empty." << '\n';
        return false;
    }

    std::regex reg { "^[a-zA-Z0-9]*$" };
    if(!std::regex_match(str, reg)){
        cout << "`Number` contains special characters including `blank_space`." << '\n';
        return false;
    }
    
    return true;
}

#include <stdexcept>
#include <ctime>

bool is_leap_year(int year){
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool validate_date(string& str){
    if(str.empty()){
        cout << "`Date` is empty." << '\n';
    }

    std::regex reg { "^([0-2][0-9]|3[0-1])/(0[1-9]|1[0-2])/([0-9]{4})$" };
    if(!std::regex_match(str, reg)){
        cout << "`Date` wrong format." << '\n';
        return false;
    }

    int day, month, year;
    sscanf(str.c_str(), "%d/%d/%d", &day, &month, &year);

    if((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30)){
        cout << "`Day` " << day << " in `Month` " << month << '\n';
        return false;
    } else if (month == 2){
        if((is_leap_year(year)) && (day > 29)){
            return false;
        } else if ((is_leap_year(year)) && (day > 28)){
            return false;
        }
    } else if (day > 31){
        return false;
    }

    return true;
}



int main(){
    string input;
    do {
        cout << "- Date: ";
        getline(cin, input);
    } while( !validate_date(input) );
    cout << input << '\n';
    
    // string str;
    // getline(cin, str);
    // std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    // cout << str << '\n';
}