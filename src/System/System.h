#ifndef SYSTEM_H
#define SYSTEM_H

#include "../Motorbike/Motorbike.h"
#include "../Member/Member.h"
#include "../Admin/Admin.h"
#include "../Request/Request.h"
#include "../define.h"
#include "../Review/Review.h"

// define file_name
#define ACCOUNT_FILE "./Data/Account.txt"
#define MOTORBIKE_FILE "./Data/Motorbike.txt"
#define RENTAL_FILE "./Data/Rental.txt"
#define REQUEST_FILE "./Data/Request.txt"
#define HISTORY_FILE "./Data/History.txt"
#define CODE_FILE "./Data/Code.txt"

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
#include <fstream>
#include <regex>
#include <cstring>
#include <algorithm>

class Admin;

class System {
    public:
        System();

        /**
         * Attributes
        */
        std::vector <Member*> member_vector;
        std::vector <Motorbike*> bike_vector;
        std::vector <Motorbike*> rental_list;
        std::unordered_map <std::string, int> code_list;

        Member* current_member = nullptr;
        Motorbike* current_bike = nullptr;

        Admin* admin;

        Motorbike* rent_bike = nullptr;
        std::vector <Motorbike*> affordable_bike_list;

        /**
         * Data
        */
        void input_data();
        void update_data();

        void input_member_list();
        void input_bike_list();
        void link_member_and_bike();
        void input_rental_list();
        void input_history_review();
        void input_request_list();
        void input_code_list();

        void update_member_file();
        void update_bike_file();
        void update_rental_file();
        void update_request_to_file();
        void update_code_to_file();
        /**
         * Tool
        */ 
        bool is_integer(std::string&);
        bool is_double(std::string&);

        bool validate_fullname(std::string&);
        bool validate_phone(std::string&);
        bool validate_id_type(std::string&);
        bool validate_number(std::string&);
        bool validate_date(std::string&);
        bool is_leap_year(int&);
        bool validate_username(std::string&);
        bool validate_login_username(std::string&);
        bool validate_password(std::string&);
        bool validate_login_password(std::string&, std::string&);
        bool recommend_password(std::string&);
        bool no_special_char_check(std::string&);
        bool validate_model(std::string&);

        std::vector<std::string> splitStr(std::string&, char);
        std::string trim(std::string&);
        Date* to_object(std::string&);
        int choice_selection(int, int);
        int count_day(Date*, Date*);
        /**
         * Feature
        */
        void welcome_screen();
        void login_menu();
        void login_as_member();
        void login_as_admin();

        // Member
        void member_menu();
        void member_view_information();
        void member_view_bike_information();
        void member_add_bike();
        void member_list_rental();
        void member_unlist_rental();
        void member_search_rent(const std::string&, std::string&, std::string& );
        void member_view_rental_list(const std::string&, Date*, Date*);
        void member_request_rent();
        void member_view_request();
        void member_top_up();

        // Guest
        void guest_menu();
        void guest_view_bike();
        void guest_registration();

        // Admin
        void admin_menu();
        void admin_view_all_members();
        void admin_view_all_bikes();
        void admin_generate_code();
};

#endif