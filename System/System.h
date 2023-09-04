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

        // Feat Function 
        std::vector<std::string> splitStr(std::string& str, char ch);

        Date* to_object(std::string& str);

        int choice_selection(int a, int b);

        void welcome_screen();

        void user_choice();

        void guest_login();

        void guest_to_member();
};

#endif