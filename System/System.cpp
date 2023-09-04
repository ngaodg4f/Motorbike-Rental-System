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
                                std::stoi(tokens.at(7)),
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
        update_file << std::to_string(mem->get_id()) << ";"
                    << mem->get_fullname() << ";"
                    << mem->get_phone() << ";"
                    << mem->get_id_type() << ";"
                    << mem->get_id_number() << ";"
                    << mem->get_license_number() << ";"
                    << mem->get_expiry_date()->to_string() << ";"
                    << std::to_string(mem->get_credit_point()) << ";"
                    << mem->get_username() << ";"
                    << mem->get_password() << ";"
                    << std::to_string(mem->get_bike_id()) << '\n';
    }

    update_file.close();
}

/**
 * Tool Function
*/
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
            view_bike_info();
            break;

        case 2:
            guest_to_member();
            break;

        case 3:
            welcome_screen();
    }
}

void System::guest_to_member(){
    int id, credit_point, bike_id;
    string username, fullname, phone;
    string id_type, id_number, license_number, expiry_date, password;
    
    id = member_vector.size();
    
    cout << "- Fullname: ";
    getline(cin >> std::ws, fullname);
    cout << "- Phone: ";
    getline(cin >> std::ws, phone);
    cout << "- ID Type: ";
    getline(cin >> std::ws, id_type);
    cout << "- ID Number: ";
    getline(cin >> std::ws, id_number);
    cout << "- License Number: ";
    getline(cin >> std::ws, license_number);
    cout << "- Expiry Date: ";
    getline(cin >> std::ws, expiry_date);
    cout << "- Usename: ";
    getline(cin >> std::ws, username);
    cout << "- Password: ";
    getline(cin >> std::ws, password);
    
    credit_point = 20;
    bike_id = 0;
    
    Member* new_member = new Member(id, fullname, phone, id_type, id_number, license_number, 
                                    to_object(expiry_date), credit_point, username, password, bike_id);

    member_vector.push_back(new_member);
}

int main(){
    System sys;
    sys.input_member_list();
    sys.welcome_screen();
}