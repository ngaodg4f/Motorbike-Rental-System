#include "System.h"
using std::cout, std::cin, std::string;

System::System(){}

/**
 * Function to input data into attributes
*/
void System::input_data(){
    input_member_list();
    input_bike_list();
    link_member_and_bike();
    input_rental_list();
}

void System::update_data(){
    update_member_file();
    update_bike_file();
    update_rental_file();
    update_request_to_file();
}

void System::input_member_list(){
    member_vector.clear();
    std::ifstream member_file (ACCOUNT_FILE);
    if(!member_file.is_open()){
        std::cerr << "Error: Can't open " << ACCOUNT_FILE << '\n';
        return;
    }

    string str;
    while( getline(member_file, str) ){
        std::vector<string> tokens;
        tokens = splitStr(str, ';');

        Member* member = new Member(
                                std::stoi(tokens.at(0)), 
                                tokens.at(1), 
                                tokens.at(2), 
                                tokens.at(3), 
                                tokens.at(4), 
                                tokens.at(5),   
                                to_object(tokens.at(6)),
                                std::stod(tokens.at(7)),
                                tokens.at(8),
                                tokens.at(9),
                                std::stoi(tokens.at(10)),
                                tokens.at(11),
                                std::stod(tokens.at(12)) );

        member_vector.push_back(member);
    }
    member_file.close();
}

void System::input_bike_list(){
    bike_vector.clear();
    std::ifstream bike_file (MOTORBIKE_FILE);
    if(!bike_file.is_open()){
        std::cerr << "Error: Can't open " << MOTORBIKE_FILE << '\n';
        return;
    }

    string str;
    while( getline(bike_file, str) ){
        std::vector<string> tokens;
        tokens = splitStr(str, ';');

        Motorbike* bike = new Motorbike(
                                    std::stoi(tokens.at(0)),
                                    std::stoi(tokens.at(1)),
                                    tokens.at(2),
                                    tokens.at(3),
                                    tokens.at(4),
                                    tokens.at(5),
                                    std::stoi(tokens.at(6)),
                                    tokens.at(7),
                                    tokens.at(8) );
        bike_vector.push_back(bike);
    }
    bike_file.close();
}

void System::link_member_and_bike(){
    for(auto mem : member_vector){
        for(auto bike : bike_vector){
            if(mem->bike_id == bike->bike_id){
                mem->link_bike(bike);
                bike->link_owner(mem);
                break;

            }
        }
    }
}

void System::input_rental_list(){
    std::ifstream rental_file (RENTAL_FILE);
    if(!rental_file.is_open()){
        std::cerr << "Error: Can't open " << RENTAL_FILE << '\n';
        return;
    }

    string str;
    while( getline(rental_file, str) ){
        std::vector<string> tokens;
        tokens = splitStr(str, ';');

        for(auto bike : bike_vector){
            if(std::stoi(tokens.at(0)) == bike->bike_id){
                bike->add_rental(std::stod(tokens.at(1)),
                                 std::stod(tokens.at(2)),
                                 to_object(tokens.at(3)),
                                 to_object(tokens.at(4)) );

                rental_list.push_back(bike);
                break;
            }
        }  
    }
    rental_file.close();
}

void System::update_member_file(){
    std::ofstream update_file (ACCOUNT_FILE);
    if(!update_file.is_open()){
        std::cerr << "Error: Can't update " << ACCOUNT_FILE << '\n';
        return;
    }
    
    for(auto mem : member_vector){
        cout << mem->id << ";"
                    << mem->fullname << ";"
                    << mem->phone << ";"
                    << mem->id_type << ";"
                    << mem->id_number << ";"
                    << mem->license_number << ";"
                    << mem->expiry_date->to_string() << ";"
                    << mem->credit_point << ";"
                    << mem->username << ";"
                    << mem->password << ";"
                    << mem->bike_id << ";"
                    << mem->location << ";"
                    << mem->renting_score << '\n';

        update_file << mem->id << ";"
                    << mem->fullname << ";"
                    << mem->phone << ";"
                    << mem->id_type << ";"
                    << mem->id_number << ";"
                    << mem->license_number << ";"
                    << mem->expiry_date->to_string() << ";"
                    << mem->credit_point << ";"
                    << mem->username << ";"
                    << mem->password << ";"
                    << mem->bike_id << ";"
                    << mem->location << ";"
                    << mem->renting_score << '\n';
    }
    update_file.close();
}

void System::update_bike_file(){
    std::ofstream update_file (MOTORBIKE_FILE);
    if(!update_file.is_open()){
        std::cerr << "Error: Can't update " << MOTORBIKE_FILE << '\n';
        return;
    }

    for(auto bike : bike_vector){
        update_file << bike->bike_id << ";"
                    << bike->member_id << ";"
                    << bike->model << ";"
                    << bike->color << ";"
                    << bike->engine_size << ";"
                    << bike->transmission_mode << ";"
                    << bike->year << ";"
                    << bike->license_plate << ";"
                    << bike->description << '\n';
    }
    update_file.close();
}

void System::update_rental_file(){
    std::ofstream update_file (RENTAL_FILE);
    if(!update_file.is_open()){
        std::cerr << "Error: Can't update " << RENTAL_FILE << '\n';
        return;
    }

    for(auto bike : bike_vector){
        if(bike->status == "AVAILABLE"){
            update_file << bike->bike_id << ";"
                        << bike->point_per_day << ";"
                        << bike->minimum_rating << ";"
                        << bike->start->to_string() << ";"
                        << bike->end->to_string() << '\n';
        }
    }
    update_file.close();
}

void System::update_request_to_file(){
    std::ofstream update_file (REQUEST_FILE);
    if(!update_file.is_open()){
        std::cerr << "Error: Can't update " << REQUEST_FILE << '\n';
        return;
    }
    for(auto mem : member_vector){
        for(auto request : mem->request_list){
            update_file << mem->id << ";"
                        << request->renter->id << ";"
                        << request->start->to_string() << ";"
                        << request->end->to_string() << ";"
                        << request->status << '\n';
        }
    }
    update_file.close();
}

/**
 * Tool Function
*/
bool System::is_integer(string& str){
    std::regex reg { "^[-+]?[0-9]+$" };
    
    return std::regex_match(str, reg);
}

bool System::is_double(string& str){
    std::regex reg { "^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$" };

    return std::regex_match(str, reg);
}

bool System::validate_fullname(string& str){
    if(str.empty()){
        cout << RED 
             << "ERROR: `Full name` is empty." << '\n'
             << RESET; 
        return false;
    }
    std::regex reg { "^[a-zA-Z0-9]{5,20}$" };
    string trim_string = trim(str);

    if(!std::regex_match(trim_string, reg)){
        cout << RED
             << "ERROR: `Full name` must contain 5 - 20 characters. No special characters." << '\n'
             << RESET;
        return false;
    }

    return true;
}
 
bool System::validate_phone(string& str){
    if(str.empty()){
        cout << RED
             << "ERROR: `Phone` is empty." << '\n'
             << RESET;
        return false;
    }

    std::regex reg { "^(0|84)[0-9]{9}$" };
    string trim_string = trim(str);
  
    if(!std::regex_match(trim_string, reg)){
        cout << RED
             << "ERROR: `Phone` must contain 10 numbers starting with 0 or 84." << '\n'
             << RESET;
        return false;
    }

    return true;
}

bool System::validate_id_type(string& str){
    if(str.empty()){
        cout << RED
             << "ERROR: `ID TYPE` is empty." << '\n';
        return false;
    }

    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    if(str != "id" && str != "passport"){
        cout << RED 
             << "ERROR: Wrong format, input `Id` or `Passport`." << '\n'
             << RESET;
        return false;
    }

    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return true;
}

bool System::validate_number(string& str){
    if(str.empty()){
        cout << RED
             << "ERROR: `Number` is empty." << '\n'
             << RESET;
        return false;
    }

    std::regex reg { "^[a-zA-Z0-9]*$" };
    if(!std::regex_match(str, reg)){
        cout << RED
             << "ERROR: `Number` contains special characters including `blank_space`." << '\n'
             << RESET;
        return false;
    }

    return true;
}

bool System::validate_date(string& str){
    if(str.empty()){
        cout << RED
             << "ERROR: `Date` is empty." << '\n'
             << RESET;
        return false;
    }

    std::regex reg { "^([0-2][0-9]|3[0-1])/(0[1-9]|1[0-2])/([0-9]{4})$" };
    if(!std::regex_match(str, reg)){
        cout << RED 
             << "ERROR: `Date` format dd/mm/yyyy. Ex: 01/01/2023" << '\n'
             << RESET;
        return false;
    }

    int day, month, year;
    sscanf(str.c_str(), "%d/%d/%d", &day, &month, &year);

    if((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30)){
        cout << RED << "ERROR: In-valid `day` input." << '\n' << RESET;
        return false;

    } else if (month == 2){
        if((is_leap_year(year)) && (day > 29)){
            cout << RED << "ERROR: In-valid `day` input." << '\n' << RESET;
            return false;

        } else if ((!is_leap_year(year)) && (day > 28)){
            cout << RED << "ERROR: In-valid `day` input." << '\n' << RESET;
            return false;
        }

    } else if (day > 31){
        cout << RED << "ERROR: In-valid `day` input." << '\n' << RESET;
        return false;
    }

    return true;
}

bool System::is_leap_year(int& year){
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool System::validate_username(string& str){
    if(str.empty()){
        cout << RED
             << "ERROR: `Username` is empty." << '\n'
             << RESET;
        return false;
    }

    std::regex reg1 { "^[a-zA-Z0-9@.]{4,18}$" };
    std::regex reg2 { "^([^@.]*[@.]?[^@.]*)$" };

    if(!std::regex_match(str, reg1)){
        cout << RED
             << "ERROR: `Username` must contain 4 - 18 characters. No special characters." << '\n'
             << "       `Username` only available for @ and ." << '\n'
             << RESET;
        return false;
    } 

    if (!std::regex_match(str, reg2)){
        cout << RED
             << "`Username` contains more than 1 '.' or '@'." << '\n'
             << RESET;
        return false;
    }

    for(auto mem : member_vector){
        if(str == mem->username){
            cout << RED
                 << "FAILED: `Username` is already taken." << '\n'
                 << RESET;
            return false;
        }
    }

    return true;
}

bool System::validate_login_username(string& str){
    if(str.empty()){
        cout << RED
             << "ERROR: `Username` is empty." << '\n'
             << RESET;
        return false;
    }

    bool is_found = false;
    for(auto mem : member_vector){
        if(str == mem->username){
            is_found = true;
            break;
        }
    }
    if(!is_found){
        cout << RED
             << "FAILED: `Username` doesn't exist." << '\n'
             << RESET;
    }

    return is_found;
}

bool System::validate_password(string& str){
    if(str.empty()){
        cout << RED
             << "ERROR: `Password` is empty." << '\n'
             << RESET;
        return false;
    }

    if( str.length() < 4 || str.find(" ") != std::string::npos ){
        cout << RED
             << "ERROR: `Password` must contains at least 4 characters with no space." << '\n'
             << RESET;
        return false;
    }

    return true;
}

bool System::validate_login_password(string& str, string& check){
    if(str.empty()){
        cout << RED
             << "ERROR: `Password` is empty." << '\n'
             << RESET;
        return false;
    }

    return str == check;
}

bool System::recommend_password(string& str){
    bool is_recommended = false;
    cout << YELLOW
         << "RECOMMEND PASSWORD: " << '\n';
    if (!std::regex_search(str, std::regex("[A-Z]"))) {
        cout << "~ Should contains at least 1 upper_case." << '\n';
        is_recommended = true;
    }

    if (!std::regex_search(str, std::regex("[a-z]"))) {
        cout << "~ Should contain at least 1 lower_case." << '\n';
        is_recommended = true;
    }

    if (!std::regex_search(str, std::regex("[0-9]"))) {
        cout << "~ Should contain at least 1 number." << '\n';
        is_recommended = true;
    }

    if (!std::regex_search(str, std::regex("[!@#$%^&*()]"))) {
        cout << "~ Should contain at least 1 special character (@, !, $, #, ...)" << '\n';
        is_recommended = true;
    }

    if ( !is_recommended ){
        cout << "NOTICE: `Password` is strong enough." << '\n';
    }
    cout << RESET;

    return true;
}

bool System::validate_model(string& str){
    if(str.empty()){
        cout << RED
             << "ERROR: `Model` is empty." << '\n'
             << RESET;
        return false;
    }

    std::regex reg { "^[a-zA-Z0-9-]{1,10}$" };
    if(!std::regex_match(str, reg)){
        cout << RED
             << "ERROR: `Model` contains max 10 characters. No special characters." << '\n'
             << RESET;
        return false;
    }

    return true;
}

bool System::no_special_char_check(string& str){
    std::regex reg { "^[a-zA-Z0-9]+$" };
    if(str.empty() || !std::regex_match(str, reg)){
        cout << RED
             << "ERROR: `Input` is empty or contains special characters." << '\n'
             << RESET;
        return false;
    }

    return true;
}

std::vector<string> System::splitStr(string& str, char ch){
    std::vector<string> data_list;
    std::stringstream ss { str };
    string token;

    while(!ss.eof()){
        getline(ss, token, ch);
        data_list.push_back(token);
    }

    return data_list;
}

string System::trim(string& str){
    string new_string;
    for(auto ch : str){
        if(ch != ' '){
            new_string += ch;
        }
    }

    return new_string;
}

Date* System::to_object(string& str){
    std::vector<string> tokens = splitStr(str, '/');
    Date* converted_date = new Date(
                                std::stoi(tokens.at(0)), 
                                std::stoi(tokens.at(1)), 
                                std::stoi(tokens.at(2)));

    return converted_date;
}

int System::choice_selection(int a, int b){
    string input_choice;
    int choice;
    bool is_valid = false;

    do {
        cout << CYAN 
             << BOLD
             << "> Your choice: "
             << RESET;
        getline(cin, input_choice);

        if( !is_integer(input_choice) ){
            cout << RED << "`Choice` is number ONLY." << RESET << '\n';

        } else {
            choice = std::stoi(input_choice);
            if(choice < a || choice > b){
                cout << RED << "No option " << choice << RESET << '\n';
                
            } else {
                is_valid = true;
            }
        }
    } while( !is_valid );
    cout << '\n';

    return choice;
}

int System::count_day(Date* start, Date* end){
    int day = start->day;
    int month = start->month;
    int year = start->year;
    int count_day = 0;
    int day_of_month;

    if(year > end->year){
        return -1; 

    } else if (year == end->year){
        if(month > end->month){
            return -1;

        } else if (month == end->month){
            if(day > end->day){
                return -1 ;
            } else if (day == end->day){
                return 0;
            }
        }
    }

    while(year <= end->year){
        switch(month){
            case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                day_of_month = 31;
                break;
            
            case 4: case 6: case 9: case 11:
                day_of_month = 30;
                break;

            case 2:
                if( (start->year% 4 == 0 && start->year% 100 != 0) || (start->year% 400 == 0) ){
                    day_of_month = 29;
                } else {
                    day_of_month = 28;
                }
                break;
        }
        
        if(month == end->month && year == end->year){
            count_day += end->day;
            break;
        }
        count_day == 0 ? count_day += (day_of_month - start->day + 1) : count_day += day_of_month;
        
        if(month < 12){
            month++;
        } else {
            month = 1;
            year++;
        }
    }
    return count_day;
}
/**
 * Feature Function
*/

void System::welcome_screen(){
    system("clear");
    cout << CYAN
         << "---------------------------------------------------------\n"
         << "|              EEET2482/COSC2082 ASSIGNMENT             |\n"
         << "|              MOTORBIKE RENTAL APPLICATION             |\n"
         << "|             Instructor: Dr. Ling Huo Chong            |\n"
         << "|                     GROUP: Group 1                    |\n"
         << "|               s3979348, Nguyen Son Tung               |\n"
         << "|             s3924993, Nguyen Le Thuc Quynh            |\n" 
         << "|             s3923010, Nguyen Dinh Minh Chau           |\n"
         << "|                 s3924729, Ho Quang Huy                |\n"
         << "---------------------------------------------------------\n"
         << RESET;

    login_menu();
}

void System::login_menu(){
    input_data();
    cout << BLUE
         << BOLD
         << "------------------------- LOGIN -------------------------\n"
         << "| 1. Guest\t2. Member\t3. Admin\t4. EXIT |\n"
         << "---------------------------------------------------------\n"
         << RESET;

    int choice = choice_selection(1, 4);
    switch(choice){
        case 1:
            system("clear");
            guest_menu();
            break;

        case 2:
            system("clear");
            cout << GREEN
                 << BOLD
                 << "---------------------------------------------------------\n"
                 << "|                     MEMBER LOGIN                      |\n" 
                 << "|                  1. Login as Member                   |\n"
                 << "|                  2. Return to Menu                    |\n"
                 << "---------------------------------------------------------\n"
                 << RESET;

            choice = choice_selection(1, 2);
            switch(choice){
                case 1: 
                    login_as_member();
                    break;

                case 2:
                    system("clear");
                    login_menu();
            }

            break;

        case 3:
            system("clear");
            cout << GREEN
                 << BOLD
                 << "---------------------------------------------------------\n"
                 << "|                      ADMIN LOGIN                      |\n" 
                 << "|                  1. Login as Admin                    |\n"
                 << "|                  2. Return to Menu                    |\n"
                 << "---------------------------------------------------------\n"
                 << RESET;

            choice = choice_selection(1, 2);
            switch(choice){
                case 1: 
                    login_as_admin();
                    break;

                case 2:
                    system("clear");
                    login_menu();
            }

            break;

        case 4:
            update_data();
            cout << CYAN << BOLD
                 << "~~~~~~~~~~ THANKS FOR COMING TO OUR COMMUNITY ~~~~~~~~~~~\n"
                 << RESET;
            exit(0);
    }
}

void System::login_as_admin(){
    string username, password;
    int count = 4;

    do {
        cout << MAGENTA << "Enter username: " << RESET;
        getline(cin, username);
    } while ( username != "admin" );

    do {
        cout << MAGENTA << "Enter password: " << RESET;
        getline(cin, password);
        count--;

        if(count == 0){
            cout << RED
                 << "FAILED: `Admin` login error." << '\n'
                 << RESET;
            login_menu();

        } else if (count != 4){
            cout << RED
                 << "ALERT: Wrong password. " 
                 << BOLD << count << " times left." << '\n'
                 << RESET;
        }
    } while ( password != "admin" );

    admin = new Admin();
    admin_menu();
}

void System::login_as_member(){
    string username, password;
    Member* temp_member;
    int count = 4;

    do {
        if(count == 0){
            cout << RED
                 << "LOGIN FAILED: Return to login menu" << '\n'
                 << RESET;
            login_menu();
        
        } else if (count != 4){
            cout << RED
                 << "ALERT: "
                 << BOLD
                 << count << " times left." << '\n'
                 << RESET;
        }

        cout << MAGENTA << "Enter username: " << RESET;
        getline(cin, username);
        count--;
    } while ( !validate_login_username(username) );
    
    for(auto mem : member_vector){
        if(username == mem->username){
            temp_member = mem;
            break;
        }
    }

    count = 4;
    do {
        if(count == 0){
            cout << RED
                 << "FAILED: `Member` login error." << '\n'
                 << RESET;
            login_menu();

        } else if (count != 4){
            cout << RED
                 << "ALERT: Wrong password. " 
                 << BOLD << count << " times left." << '\n'
                 << RESET;
        }

        cout << MAGENTA << "Enter password: " << RESET;
        getline(cin, password);
        count--;

    } while ( !validate_login_password(password, temp_member->password) );
    
    current_member = temp_member;
    current_bike = current_member->bike;

    member_menu();
}

// MEMBER
void System::member_menu(){
    cout << GREEN
         << BOLD
         << "--------------------- MEMBER MENU ----------------------\n"
         << "|              ~ ~ ~ HAVE A NICE DAY ~ ~ ~              |\n" 
         << "|               1. View personal details                |\n"
         << "|                2. View your motorbike                 |\n"
         << "|                3. Add a new motorbike                 |\n"
         << "|               4. List bike for renting                |\n"
         << "|              5. Un-List bike for rental               |\n"
         << "|               6. Request renting a bike               |\n"
         << "|              7. View requests from others             |\n"
         << "|                       8. EXIT                         |\n"
         << "---------------------------------------------------------\n"
         << RESET;

    int choice = choice_selection(1, 8);
    switch(choice){
        case 1:
            member_view_information();
            member_menu();
            break;

        case 2:
            member_view_bike_information();
            member_menu();
            break;

        case 3:
            member_add_bike();
            member_menu();
            break;

        case 4:
            member_list_rental();
            member_menu();
            break;

        case 5:
            member_unlist_rental();
            member_menu();
            break;

        case 6:
            member_request_rent();
            member_menu();
            break;

        case 7:
            member_view_request();
            member_menu();
            break;

        case 8: 
            system("clear");
            update_data();
            input_data();

            login_menu();
    }
}

void System::member_view_information(){
    cout << YELLOW
         << std::left << std::setw(10) << "ID" 
         << std::left << std::setw(20) << "FULL_NAME" 
         << std::left << std::setw(15) << "PHONE" 
         << std::left << std::setw(15) << "ID_TYPE"
         << std::left << std::setw(15) << "ID_NUMBER"
         << std::left << std::setw(15) << "LICENSE_NO"
         << std::left << std::setw(15) << "EXPIRY_DATE"
         << std::left << std::setw(15) << "CREDITS"
         << std::left << std::setw(15) << "LOCATION" << '\n'
         << RESET;
        
        current_member->view_personal_info();
        cout << '\n';
}

void System::member_view_bike_information(){
    if(current_bike == nullptr){
        cout << RED
             << "ERROR: `Bike` not found." << '\n'
             << RESET;

        cout << '\n';
        return;

    } else {
        cout << YELLOW
             << std::left << std::setw(15) << "MODEL" 
             << std::left << std::setw(15) << "COLOR" 
             << std::left << std::setw(15) << "ENGINE_SIZE" 
             << std::left << std::setw(20) << "TRANSMISSION_MODE"
             << std::left << std::setw(8) << "YEAR"
             << std::left << std::setw(17) << "LICENSE_PLATE"
             << std::left << std::setw(15) << "DESCRIPTION" << '\n'
             << RESET;

        current_bike->view_bike_info();
        cout << '\n';
    }
}

void System::member_add_bike(){
    if(current_bike != nullptr){
        cout << RED
             << "ERROR: `Bike` found." << '\n'
             << "ALERT: Do you want to add new one ?" << '\n'
             << RESET;
        
        string confirm;
        bool is_valid_input;
        do {
            cout << MAGENTA << "> Y/N: " << RESET;
            getline(cin, confirm);
        
            is_valid_input = ! (confirm != "Y" && 
                                confirm != "y" && 
                                confirm != "N" && 
                                confirm != "n" );

            if(!is_valid_input){
                cout << RED << "ERROR: `Input` Y or N only." << '\n' << RESET;
            }
        } while ( !is_valid_input );

        if(confirm == "N" || confirm == "n"){
            member_menu();
        } 
        // bike_vector.erase(bike_vector.begin() + current_bike->bike_id);
    }

    int id, member_id;
    string model, color, engine_size, transmission_mode, license_plate, description;
    string year;

    id = current_bike->bike_id;
    member_id = current_member->id;

    cout << GREEN
         << "----------------- ADDING A NEW MOTORBIKE ----------------\n"
         << RESET;

    do {
        cout << MAGENTA << "Enter model: " << RESET;
        getline(cin, model);
    } while ( !validate_model(model) );

    do {
        cout << MAGENTA << "Enter color: " << RESET;
        getline(cin, color);
    } while ( !no_special_char_check(color) );

    do {
        cout << MAGENTA << "Enter engine size: " << RESET;
        getline(cin, engine_size);
    } while ( !no_special_char_check(engine_size) );

    do {
        cout << MAGENTA << "Enter transmission mode: " << RESET;
        getline(cin, transmission_mode);
    } while ( !no_special_char_check(transmission_mode) );

    do {
        cout << MAGENTA << "Enter year: " << RESET;
        getline(cin, year);
    } while ( !is_integer(year) );

    do {
        cout << MAGENTA << "Enter license plate: " << RESET;
        getline(cin, license_plate);
    } while ( !no_special_char_check(license_plate) );

    do {
        cout << MAGENTA << "Enter description: " << RESET;
        getline(cin, description);
    } while ( description.length() > 30);

    Motorbike* bike = new Motorbike(
                                id,
                                member_id,
                                model,
                                color,
                                engine_size,
                                transmission_mode,
                                std::stoi(year),
                                license_plate,
                                description );
    bike_vector.at(id - 1) = bike;
    current_bike = bike;

    for(auto mem : member_vector){
        if(mem->username == current_member->username){
            mem->bike_id = id;
            
            mem->link_bike(bike);
            bike->link_owner(mem);
            break;
        }
    }
    cout << '\n';
    cout << current_member->bike_id << '\n';

    update_data();
    input_data();
}

void System::member_list_rental(){
    if(current_bike == nullptr){
        cout << RED
             << "ERROR: `Bike` need to be added first." << '\n'
             << RESET;
        return;
    }
    
    if(current_bike->status == "AVAILABLE"){
        cout << RED
             << "`Bike` is currently AVAILABLE. Un-list bike first." << '\n'
             << RESET;
        return;
    }

    cout << GREEN
         << "-------------- LISTING MOTORBIKE FOR RENTAL -------------\n"
         << RESET;

    string point, rating;
    do {
        cout << MAGENTA << "Enter points/day: " << RESET;
        getline(cin, point);
    } while ( !is_double(point) );

    do {
        cout << MAGENTA << "Minimum rating: " << RESET;
        getline(cin, rating);
        if(std::stod(rating) > 10){
            cout << RED
                 << "ERROR: `Rating` max is 10." << '\n'
                 << RESET;
        }
    } while ( !is_double(rating) || std::stod(rating) > 10);

    string start, end;
    cout << "Renting Period: " << '\n';
    cout << MAGENTA << "Rental Period: " << RESET;
    do {
        cout << MAGENTA << "Enter start: " << RESET;
        getline(cin, start);
    } while( !validate_date(start) ) ;

    int day_count;
    do {
        do {
            cout << MAGENTA << "Enter end: " << RESET;
            getline(cin, end);
        } while( !validate_date(end) ) ;

        day_count = count_day(to_object(start), to_object(end));
        if(day_count <= 0){
            cout << RED
                 << "ERROR: `End` is same or earlier than `Start`." << '\n'
                 << RESET;
        }

    } while ( day_count <= 0);

    current_bike->add_rental( std::stod(point), std::stod(rating), to_object(start), to_object(end) );
    rental_list.push_back( current_bike );

    update_data();
    input_data();
}

void System::member_unlist_rental(){
    if(current_bike == nullptr){
        cout << RED
             << "ERROR: `Bike` need to be added first." << '\n'
             << RESET;
        return;
    }
    if(current_bike->status == "NOT_AVAILABLE"){
        cout << RED
             << "ERROR: `Bike` need to be listed first." << '\n'
             << RESET;
        return;
    }
    for(int i = 0; i < rental_list.size(); i++){
        if(rental_list.at(i)->bike_id == current_bike->bike_id){
            rental_list.at(i)->reset_condition();
            rental_list.erase( rental_list.begin() + i );

            break;
        }
    }
    cout << GREEN
         << "---------------- UN-LISTING SUCCESSFULLY ---------------\n"
         << RESET;
        
    update_data();
    input_data();
}

void System::member_search_rent(const string& location, string& start, string& end){
    cout << GREEN
         << "------------------- FILTER FOR REQUEST ------------------\n"
         << RESET;

    do {
        cout << MAGENTA << "Enter start: " << RESET;
        getline(cin, start);
    } while( !validate_date(start) ) ;

    int day_rent;
    do {
        do {
            cout << MAGENTA << "Enter end: " << RESET;
            getline(cin, end);
        } while( !validate_date(end) ) ;

        day_rent = count_day(to_object(start), to_object(end));
        if(day_rent <= 0){
            cout << RED
                 << "ERROR: `End` is same or earlier than `Start`." << '\n'
                 << RESET;
        }
    } while ( day_rent <= 0);

    cout << '\n';
    cout << GREEN
         << "YOUR CURRENT STATUS\n"
         << RESET;

    cout << WHITE;
    cout << "Location: " << location << '\n';
    cout << "Points: " << current_member->credit_point
         << std::right << std::setw(15)
         << "Rating: " << current_member->renting_score << '\n';

    cout << "Start: " << to_object(start)->to_string()  << '\n';

    cout << "End: " << to_object(end)->to_string() << '\n';
    cout << RESET;

    member_view_rental_list(location, to_object(start), to_object(end));
}

void System::member_view_rental_list(const string& search_location, Date* start_date, Date* end_date){
    cout << YELLOW
         << std::left << std::setw(10) << "BIKE_ID"
         << std::left << std::setw(13) << "MODEL"
         << std::left << std::setw(15) << "ENGINE_SIZE"
         << std::left << std::setw(15) << "POINT / DAY"
         << std::left << std::setw(15) << "MIN_RATING"
         << std::left << std::setw(15) << "START_DATE"
         << std::left << std::setw(15) << "END_DATE"
         << std::left << std::setw(15) << "DESCRIPTION" << '\n'
         << RESET;

    bool is_found = false;
    for(auto rental : rental_list){
        double total_consuming = count_day(start_date, end_date) * rental->point_per_day;

        if (rental->owner->location != search_location){
            continue;

        } else if ( count_day(start_date, rental->start) > 0){
            continue;
            
        } else if ( count_day(end_date, rental->end) < 0){
            continue;

        } else if (current_member->credit_point < total_consuming){
            continue;

        } else if (current_member->renting_score < rental->minimum_rating){
            continue;

        } else {
            is_found = true;
            cout << YELLOW
                 << std::left << std::setw(10) << rental->bike_id
                 << std::left << std::setw(13) << rental->model
                 << std::left << std::setw(15) << rental->engine_size
                 << std::left << std::setw(15) << rental->point_per_day
                 << std::left << std::setw(15) << rental->minimum_rating
                 << std::left << std::setw(15) << rental->start->to_string()
                 << std::left << std::setw(15) << rental->end->to_string()
                 << std::left << std::setw(15) << rental->description << '\n'
                 << RESET;

            affordable_bike_list.push_back( rental );
        }
    }
    
    if( !is_found ){
        cout << RED
             << "ERROR: `Motorbike` not found." << '\n'
             << RESET;

        cout << '\n';
        member_menu();
    }

    cout << '\n';
}

void System::member_request_rent(){
    if(current_member->rented_bike != nullptr){
        cout << RED
             << "`Member` can only occupy 1 motorbike." << '\n'
             << RESET;

        member_menu();
    }

    string location = current_member->location;
    string start, end;
    member_search_rent(location, start, end);
    
    string input;
    Motorbike* found_bike;
    
    auto f = bike_vector.end();
    do {
        do {
            cout << MAGENTA << "Enter `ID` to rent (0 to EXIT): " << RESET;
            getline(cin, input);
        } while ( !is_integer(input) );

        if(input == "0"){
            member_menu();
        }

        for(auto bike : affordable_bike_list){
            if(bike->bike_id == std::stoi(input)){
                found_bike = bike;
                f = std::find( rental_list.begin(), rental_list.end(), found_bike );
                break;  

            }
        }
        if(f == bike_vector.end()){
            cout << RED 
                 << "ERROR: `Motorbike` not found." << '\n'
                 << RESET;
        }

    } while ( f == bike_vector.end() );

    Request* request = new Request ( current_member, to_object(start), to_object(end) );
    found_bike->owner->get_new_request( request );

    cout << YELLOW << "`Request` rent completed" << '\n' << RESET;
}   
    
void System::member_view_request(){
    if(current_member->request_list.size() == 0){
        cout << RED
             << "ERROR: `Request` not found." << '\n'
             << RESET;
        return;
    }

    current_member->view_request();
    
    string input;
    int chosen_id;
    bool is_found = false;
    Date* start;
    Date* end;
    double total_consuming;

    do {
        do {
            cout << MAGENTA << "Enter `id` to accept (0 to EXIT): " << RESET;
            getline(cin, input);

            if(input == "0"){
                member_menu();
            } 
        } while ( !is_integer(input) );

        chosen_id = std::stoi( input );
    
        for(auto request : current_member->request_list){
            if(chosen_id == request->renter->id){
                is_found = true;

                if(request->renter->rented_bike != nullptr){
                    cout << RED
                         << "ERROR: `Renter` already occupied another bike." << '\n'
                         << RESET;
                    is_found = false;

                } else {
                    start = request->start;
                    end = request->end;
                }
                break;
            }
        }
    } while ( !is_found );

    for(auto mem : member_vector){
        if(chosen_id == mem->id){
            mem->rented_bike == current_bike;
            total_consuming = count_day(start, end) * current_bike->point_per_day;

            mem->use_credit_point( total_consuming );
            current_member->earn_credit_point( total_consuming) ;
            break;
        }
    }
    
    bool is_declined = false;
    Request* target;
    for(int i = 0; i < current_member->request_list.size(); i++){
        target = current_member->request_list.at(i);
        if(count_day(end, target->start) <= 0 || count_day(target->end, start) <= 0){
            is_declined = true;
        }

        if(is_declined){
            current_member->request_list.erase(current_member->request_list.begin() + i);

        } else {
            target->get_accepted();
        }
    }

    update_data();
    input_data();
}


// GUEST
void System::guest_menu(){
    cout << GREEN
         << BOLD
         << "---------------- |WELCOME TO COMMUNITY| -----------------\n"
         << "|                      GUEST MENU                       |\n" 
         << "|                1. View all motorbikes                 |\n"
         << "|                2. Member registration                 |\n"
         << "|                      3. EXIT                          |\n"
         << "---------------------------------------------------------\n"
         << RESET;

    int choice = choice_selection(1, 3);
    switch(choice){
        case 1:
            guest_view_bike();
            guest_menu();
            break;

        case 2:
            guest_registration();
            guest_menu();
            break;

        case 3:
            system("clear");
            login_menu();
    }

}

void System::guest_view_bike(){
    cout << YELLOW
         << std::left << std::setw(10) << "BIKE_ID" 
         << std::left << std::setw(20) << "OWNER_NAME" 
         << std::left << std::setw(16) << "MODEL" 
         << std::left << std::setw(15) << "ENGINE_SIZE"
         << std::left << std::setw(15) << "YEAR MADE"
         << std::left << std::setw(15) << "DESCRIPTION" << '\n';

    for(auto bike : bike_vector){
        cout << YELLOW
             << std::left << std::setw(10) << bike->bike_id
             << std::left << std::setw(20) << bike->owner->fullname
             << std::left << std::setw(16) << bike->model
             << std::left << std::setw(15) << bike->engine_size
             << std::left << std::setw(15) << bike->year
             << std::left << std::setw(15) << bike->description << '\n' 
             << RESET;
    }
    cout << '\n';
}

void System::guest_registration(){
    int id, bike_id;
    string username, fullname, phone;
    string id_type, id_number, license_number, expiry_date, password;
    double credit_point, renting_score;

    id = member_vector.size() + 1;
    cout << GREEN
         << "------------------ MEMBER REGISTRATION ------------------\n"
         << RESET;

    do {
        cout << MAGENTA << "Enter your full-name: " << RESET;
        getline(cin, fullname);
    } while ( !validate_fullname( fullname ) );

    do {
        cout << MAGENTA << "Enter phone number: " << RESET;
        getline(cin, phone);
    } while ( !validate_phone( phone ) );

    do {
        cout << MAGENTA << "ID Type (Id/Passport): " << RESET;
        getline(cin, id_type);
    } while ( !validate_id_type( id_type ) );
    
    do {
        cout << MAGENTA << "Enter ID number: " << RESET;
        getline(cin, id_number);
    } while ( !validate_number( id_number ) );

    do {
        cout << MAGENTA << "Enter license number: " << RESET;
        getline(cin, license_number);
    } while ( !validate_number( license_number ) );
    
    do {
        cout << MAGENTA << "Enter expiry-date: " << RESET;
        getline(cin, expiry_date);
    } while ( !validate_date( expiry_date ) );

    do {
        cout << MAGENTA << "Enter username: " << RESET;
        getline(cin, username);
    } while ( !validate_username( username ) );
    
    string confirm;
    bool is_valid_input;
    do {
        do {
            cout << MAGENTA << "Enter password: " << RESET;
            getline(cin, password);
        } while ( !validate_password(password) );

        if( recommend_password(password) ){
            cout << YELLOW << "Do you want to re-enter password ?" << '\n'
                 << RESET;
            do {
                cout << CYAN << BOLD << "> Y/N: " << RESET;
                getline(cin, confirm);
                is_valid_input = !( confirm != "Y" && 
                                    confirm != "y" && 
                                    confirm != "N" && 
                                    confirm != "n" );

                if(!is_valid_input){
                    cout << RED << "EEROR: `Input` Y or N only." << '\n' 
                         << RESET;
                }
            } while ( !is_valid_input );
        }

    } while (confirm == "Y" || confirm == "y");
    
    credit_point = INITIAL_CREDITS;
    bike_id = 0;
    renting_score = 0;

    cout << MAGENTA
         << "LOCATION:\t1. SAIGON\t2. HANOI" << '\n'
         << RESET;
    
    int choice = choice_selection(1, 2);
    string location = LOCATIONS[choice - 1];

    cout << YELLOW
         << "---------------------------------------------------------\n"
         << "|                 REGISTRATION COMPLETED !              |\n"
         << "|            20 points is added to your account         |\n"
         << "---------------------------------------------------------\n"
         << RESET;

    Member* new_member = new Member(id, fullname, phone, id_type, id_number, license_number, 
                                    to_object(expiry_date), credit_point, username, password, 
                                    bike_id, location, renting_score);

    member_vector.push_back( new_member );
    cout << '\n';

    update_data();
    input_data();
}


// ADMIN
void System::admin_menu(){
    cout << GREEN
         << BOLD
         << "-------------------- ADMIN DASHBOARD --------------------\n"
         << "|                  1. View all members                  |\n"
         << "|                2. View all motorbikes                 |\n"
         << "|                       3. EXIT                         |\n"
         << "---------------------------------------------------------\n"
         << RESET;

    int choice = choice_selection(1, 3);
    switch(choice){
        case 1:
            admin_view_all_members();
            admin_menu();
            break;

        case 2:
            admin_view_all_bikes();
            admin_menu();
            break;

        case 3:
            system("clear");
            login_menu();
    }
}

void System::admin_view_all_members(){
    cout << YELLOW
         << std::left << std::setw(10) << "ID" 
         << std::left << std::setw(20) << "FULL_NAME" 
         << std::left << std::setw(15) << "PHONE" 
         << std::left << std::setw(15) << "ID_TYPE"
         << std::left << std::setw(15) << "ID_NUMBER"
         << std::left << std::setw(15) << "LICENSE_NO"
         << std::left << std::setw(15) << "EXPIRY_DATE"
         << std::left << std::setw(15) << "CREDITS"
         << std::left << std::setw(15) << "LOCATION"<< '\n'
         << RESET;

    for(auto mem : member_vector){
        mem->view_personal_info();
    }
}

void System::admin_view_all_bikes(){
    cout << YELLOW
         << std::left << std::setw(15) << "MODEL" 
         << std::left << std::setw(15) << "COLOR" 
         << std::left << std::setw(15) << "ENGINE_SIZE" 
         << std::left << std::setw(20) << "TRANSMISSION_MODE"
         << std::left << std::setw(8) << "YEAR"
         << std::left << std::setw(17) << "LICENSE_PLATE"
         << std::left << std::setw(15) << "DESCRIPTION" << '\n'
         << RESET;

    for(auto bike : bike_vector){
        bike->view_bike_info();
    }
}