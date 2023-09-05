#ifndef SYSTEM_H
#define SYSTEM_H

#include "../Motorbike/Motorbike.h"
#include "../Member/Member.h"

// include to check the path ...
// #include "../Data/Account.txt"

// define file_name
#define ACCOUNT_FILE "../Data/Account.txt"


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <regex>
#include <cstring>

class Member;

class System {
    public:
        // Constructor
        System();

        // Attribute to manage the class
        std::vector<Member*> member_vector;

        // Function to input data into attributes
        void input_member_list();

        void update_member_file();

        // Tool Function 
        bool validate_fullname(std::string& str);

        bool validate_phone(std::string& str);

        bool validate_id_type(std::string& str);

        bool validate_id_license_number(std::string& str);

        bool validate_date(std::string& str);

        bool is_leap_year(int& year);

        bool validate_username(std::string& str);

        bool validate_password(std::string& str);

        bool recommend_password(std::string& str);

        std::vector<std::string> splitStr(std::string& str, char ch);

        std::string trim(std::string& str);

        Date* to_object(std::string& str);

        int choice_selection(int a, int b);

        // Feature Function
        void welcome_screen();

        void user_choice();

        void guest_login();

        void member_registration();
};

#endif