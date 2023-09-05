#ifndef SYSTEM_H
#define SYSTEM_H

#include "../Motorbike/Motorbike.h"
#include "../Member/Member.h"

// include to check the path ...
// #include "../Data/Account.txt"

// define file_name
#define ACCOUNT_FILE "../Data/Account.txt"
#define MOTORBIKE_FILE "../Data/Motorbike.txt"


#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>
#include <regex>
#include <cstring>

class Member;

class System {
    public:
        System();

        /**
         * Attributes
        */
        std::vector <Member*> member_vector;
        std::vector <Motorbike*> bike_vector;

        /**
         * Data
        */
        void input_member_list();

        void update_member_file();

        void input_bike_list();

        /**
         * Tool
        */ 
        bool is_integer(std::string& str);
        
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

        /**
         * Feature
        */
        void guest_view_bike();

        void welcome_screen();

        void user_choice();

        void guest_login();

        void member_registration();
};

#endif