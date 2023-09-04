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

    while(getline(member_file, str)){
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
                    << mem->bike_id << ";"
                    << mem->username << ";"
                    << mem->password << '\n';
    }

    update_file.close();
}

/**
 * Tool Function
*/
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
    int choice;
    do {
        cout << "> Your choice: ";
        cin >> choice;
        if(choice < a || choice > b){
            std::cerr << "Error with option " << choice << '\n';
        }

    } while(choice < a || choice > b);

    return choice;
}

/**
 * Feature Function
*/
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
            guest_login();
            break;

        case 2:
            cout << "LOGIN AS MEMBER" << '\n';
            break;

        case 3:
            cout << "LOGIN AS ADMIN" << '\n';
            break;

        case 4:
            update_member_file();
            exit(0);
    }
}

void System::guest_login(){
    cout << "LOGIN AS GUEST" << '\n';
    cout << "-----MENU-----" << '\n';
    cout << "1. View all motorbikes" << '\n';
    cout << "2. Member registration" << '\n';
    cout << "3. Exit" << '\n';

    int choice = choice_selection(1, 3);

    switch(choice){
        case 1:
            cout << "------INFORMATION------" << '\n';
            // need a fix
            view_bike_info();
            welcome_screen();
            break;

        case 2:
            member_registration();
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
    
    cin.ignore();
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

    
    cout << "- Usename: ";
    getline(cin >> std::ws, username);
    cout << "- Password: ";
    getline(cin >> std::ws, password);
    
    credit_point = 20;
    bike_id = 0;
    
    Member* new_member = new Member(id, fullname, phone, id_type, id_number, license_number, 
                                    to_object(expiry_date), credit_point, username, password, bike_id);

    member_vector.push_back(new_member);

    welcome_screen();
}

int main(){
    System sys;
    sys.input_member_list();
    sys.welcome_screen();
}