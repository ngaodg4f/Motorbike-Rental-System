#include "System.h"
using std::cout, std::cin, std::string;

System::System(){}

/**
 * Function to input data into attributes
*/
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
                                std::stoi(tokens.at(10)) );

        member_vector.push_back(member);
    }
    member_file.close();
}

void System::update_member_file(){
    std::ofstream update_file (ACCOUNT_FILE);
    if(!update_file.is_open()){
        std::cerr << "Error: Can't update " << ACCOUNT_FILE << '\n';
        return;
    }

    for(auto* mem : member_vector){
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
                    << mem->bike_id << '\n';
    }

    update_file.close();
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

        // cout << std::stoi(tokens.at(0)) << '\n';
        // cout << std::stoi(tokens.at(1)) << '\n';
        // cout << std::stoi(tokens.at(6)) << '\n';
        // cout << tokens.at(2) << '\n';
        // cout << tokens.at(3) << '\n';
        // cout << tokens.at(4) << '\n';
        // cout << tokens.at(5) << '\n';
        // cout << tokens.at(7) << '\n';
        // cout << tokens.at(8) << '\n';

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

/**
 * Tool Function
*/
bool System::is_integer(string& str){
    std::regex reg { "^[-+]?[0-9]+$" };

    return std::regex_match(str, reg);
}

bool System::validate_fullname(string& str){
    if(str.empty()){
        cout << "`Full name` is empty." << '\n';
        return false;
    }
    std::regex reg { "^[a-zA-Z0-9]{5,20}$" };
    string trim_string = trim(str);

    if(!std::regex_match(trim_string, reg)){
        cout << "`Full name` must contain 8 - 20 characters with no special characters." << '\n';
        return false;
    }

    return true;
}

bool System::validate_phone(string& str){
    if(str.empty()){
        cout << "`Phone` is empty." << '\n';
        return false;
    }

    std::regex reg { "^(0|84)[0-9]{9}$" };
    string trim_string = trim(str);
  
    if(!std::regex_match(trim_string, reg)){
        cout << "`Phone` must contain 10 numbers with no special character." << '\n';
        cout << "Either start with 0 or 84." << '\n';
        return false;
    }

    return true;
}

bool System::validate_id_type(string& str){
    if(str.empty()){
        cout << "`ID TYPE` is empty." << '\n';
        return false;
    }

    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    if(str != "id" && str != "passport"){
        cout << "Wrong format. `Id` or `Passport` is available." << '\n';
        return false;
    }

    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return true;
}

bool System::validate_id_license_number(string& str){
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

bool System::validate_date(string& str){
    if(str.empty()){
        cout << "`Date` is empty." << '\n';
        return false;
    }

    std::regex reg { "^([0-2][0-9]|3[0-1])/(0[1-9]|1[0-2])/([0-9]{4})$" };
    if(!std::regex_match(str, reg)){
        cout << "`Date` format dd/mm/yyyy." << '\n';
        cout << "Ex: 01/01/2023" << '\n';
        return false;
    }

    int day, month, year;
    sscanf(str.c_str(), "%d/%d/%d", &day, &month, &year);

    if((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30)){
        cout << "`Day` " << day << " in `Month` " << month << '\n';
        return false;

    } else if (month == 2){
        if((is_leap_year(year)) && (day > 29)){
            cout << "`Day` " << day << " February, `Year` " << year << '\n';
            return false;

        } else if ((!is_leap_year(year)) && (day > 28)){
            cout << "`Day` " << day << " February, `Year` " << year << '\n';
            return false;
        }

    } else if (day > 31){
        return false;
    }

    return true;

}

bool System::is_leap_year(int& year){
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool System::validate_username(string& str){
    if(str.empty()){
        cout << "`Username` is empty." << '\n';
        return false;
    }

    std::regex reg1 { "^[a-zA-Z0-9@.]{4,18}$" };
    std::regex reg2 { "^([^@.]*[@.]?[^@.]*)$" };

    if(!std::regex_match(str, reg1)){
        cout << "`Username` contains 5 - 18 characters with no special characters." << '\n';
        cout << "`Username` only available for @ and ." << '\n';
        return false;
    } 
    if (!std::regex_match(str, reg2)){
        cout << "`Username` contains more than 1 '@' or '.'" << '\n';
        return false;
    }

    for(auto mem : member_vector){
        if(str == mem->username){
            cout << "`Username` is already taken." << '\n';
            return false;
        }
    }

    return true;
}

bool System::validate_login_username(string& str){
    if(str.empty()){
        cout << "`Username` is empty." << '\n';
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
        cout << "`Username` doesn't exist." << '\n';
    }

    return is_found;
}

bool System::validate_password(string& str){
    if(str.empty()){
        cout << "`Password` is empty." << '\n';
        return false;
    }

    if(str.length() < 6 || str.find(" ") != std::string::npos){
        cout << "`Password` must at least 6 characters with no space." << '\n';
        return false;
    }

    return true;
}

bool System::validate_login_password(string& str, string& check){
    if(str.empty()){
        cout << "`Password` is empty." << '\n';
        return false;
    }

    if(str != check){
        cout << "`Password` is wrong. Check again." << '\n';
    }

    return str == check;
}

bool System::recommend_password(string& str){
    bool is_recommended = false;
    cout << "Recommended `Password`: " << '\n';
    if (!std::regex_search(str, std::regex("[A-Z]"))) {
        cout << "- Contains at least 1 upper_case." << '\n';
        is_recommended = true;
    }

    if (!std::regex_search(str, std::regex("[a-z]"))) {
        cout << "- Contains at least 1 lower_case." << '\n';
        is_recommended = true;
    }

    if (!std::regex_search(str, std::regex("[0-9]"))) {
        cout << "- Contains at least 1 number." << '\n';
        is_recommended = true;
    }

    if (!std::regex_search(str, std::regex("[!@#$%^&*()]"))) {
        cout << "- Contains at least 1 special character (@, !, $, #, ...)" << '\n';
        is_recommended = true;
    }

    return is_recommended;
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
    bool is_not_valid = true;

    do {
        cout << "> Your choice: ";
        getline(cin, input_choice);

        if( !is_integer(input_choice) ){
            cout << "`Choice` is number ONLY." << '\n';

        } else {
            choice = std::stoi(input_choice);
            if(choice < a || choice > b){
                cout << "No option " << choice << '\n';
                
            } else {
                is_not_valid = false;
            }
        }

    } while( is_not_valid );

    return choice;
}

/**
 * Feature Function
*/
void System::guest_view_bike(){
    cout << "------INFORMATION------" << '\n';
    cout << std::left << std::setw(10) << "BIKE_ID" 
         << std::left << std::setw(13) << "OWNER_ID" 
         << std::left << std::setw(16) << "MODEL" 
         << std::left << std::setw(15) << "ENGINE_SIZE"
         << std::left << std::setw(15) << "YEAR MADE"
         << std::left << std::setw(15) << "DESCRIPTION" << '\n';

    for(auto bike : bike_vector){
        cout << std::left << std::setw(10) << bike->bike_id
             << std::left << std::setw(13) << bike->member_id
             << std::left << std::setw(16) << bike->model
             << std::left << std::setw(15) << bike->engine_size
             << std::left << std::setw(15) << bike->year
             << std::left << std::setw(15) << bike->description << '\n';
    }
}

void System::welcome_screen(){
    cout << "EEET2482/COSC2082 ASSIGNMENT" << '\n';
    cout << "MOTORBIKE RENTAL APPLICATION" << '\n';
    cout << "Instructor: Dr. Ling Huo Chong" << '\n';
    cout << "Group: Group 1" << '\n';
    cout << "s3979348, Nguyen Son Tung" << '\n';
    cout << "s3924993, Nguyen Le Thuc Quynh" << '\n';
    cout << "s3923010, Nguyen Dinh Minh Chau" << '\n';
    cout << "s2924729, Ho Quang Huy" << '\n';
    cout << '\n';
    
    cout << "----------------- LOGIN -----------------" << '\n';
    cout << "1. Guest\t2. Member\t3. Admin\t4. Exit" << '\n'; 
    user_choice();
}

void System::user_choice(){
    int choice = choice_selection(1, 4);

    switch(choice){
        case 1:
            cout << "LOGIN AS GUEST" << '\n';
            guest_login();
            break;

        case 2:
            cout << "LOGIN AS MEMBER" << '\n';
            member_login();
            break;

        case 3:
            cout << "LOGIN AS ADMIN" << '\n';
            break;

        case 4:
            update_member_file();
            exit(0);
    }
}

void System::member_login(){
    string username, password;
    Member* temp_member;

    do {
        cout << "Username: ";
        getline(cin, username);
    } while( !validate_login_username(username) );
    
    for(auto mem : member_vector){
        if(username == mem->username){
            temp_member = mem;
            break;
        }
    }
    string check = temp_member->password;
    
    do {
        cout << "Password: ";
        getline(cin, password);
    } while ( !validate_login_password(password, check) );

    current_member = temp_member;
}

void System::guest_login(){
    cout << "-----MENU-----" << '\n';
    cout << "1. View all motorbikes" << '\n';
    cout << "2. Member registration" << '\n';
    cout << "3. Exit" << '\n';

    int choice = choice_selection(1, 3);

    switch(choice){
        case 1:
            guest_view_bike();
            guest_login();
            break;

        case 2:
            member_registration();
            guest_login();
            break;

        case 3:
            welcome_screen();
    }

}

void System::member_registration(){
    int id, bike_id;
    string username, fullname, phone;
    string id_type, id_number, license_number, expiry_date, password;
    double credit_point;

    id = member_vector.size() + 1;
    
    do {
        cout << "- Full Name: ";
        getline(cin, fullname);
    } while ( !validate_fullname(fullname) );

    do {
        cout << "- Phone: ";
        getline(cin, phone);
    } while ( !validate_phone(phone) );

    do {
        cout << "- ID Type (Id/Passport): ";
        getline(cin, id_type);
    } while ( !validate_id_type(id_type) );
    
    do {
        cout << "- ID Number: ";
        getline(cin, id_number);
    } while ( !validate_id_license_number(id_number) );

    do {
        cout << "- License Number: ";
        getline(cin, license_number);
    } while ( !validate_id_license_number(license_number) );
    
    do {
        cout << "- Expiry Date: ";
        getline(cin, expiry_date);
    } while ( !validate_date(expiry_date) );

    do {
        cout << "- Usename: ";
        getline(cin, username);
    } while ( !validate_username(username) );
    
    string confirm;
    bool is_valid_input;
    do {
        do {
            cout << "- Password: ";
            getline(cin, password);
        } while ( !validate_password(password) );

        if( recommend_password(password) ){
            cout << "Do you want to re-enter password ?" << '\n';
            do {
                cout << "> Y/N: ";
                getline(cin, confirm);
                is_valid_input = !(confirm != "Y" && confirm != "y" && confirm != "N" && confirm != "n");
                // yes
                if(!is_valid_input){
                    cout << "`Input` Y or N only." << '\n';
                }
            } while ( !is_valid_input );
        }

    } while (confirm == "Y" || confirm == "y");
    
    credit_point = 20;
    bike_id = 0;

    cout << "--------------------------------------------" << '\n';
    cout << "Confirmation: Member-registration completed." << '\n';
    cout << "You have 20 credits point." << '\n';
    cout << "--------------------------------------------" << '\n';
    cout << '\n';

    Member* new_member = new Member(id, fullname, phone, id_type, id_number, license_number, 
                                    to_object(expiry_date), credit_point, username, password, bike_id);

    member_vector.push_back(new_member);

    welcome_screen();
}

int main(){
    System sys;
    sys.input_member_list();
    sys.input_bike_list();
    sys.welcome_screen();
}