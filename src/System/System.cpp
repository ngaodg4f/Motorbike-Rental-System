#include "System.h"
using std::cout, std::cin, std::string;

System::System(){}

/**
 * function input data will read all data from data files ../Data/.
 * it will clear all the vectors currently in the system (except for code file) and read them again in files if the files can be opened
 * all the data will be read as a string data type and assign to the attribute using type casting if needed 
 * vector<string> tokens are used to separate string of line of a file when approach the character comma ';' 
 */
void System::input_data(){ 
    input_member_list();
    input_bike_list();
    link_member_and_bike();
    input_rental_list();
    input_request_list();
    input_history_review();
    input_code_list();
}

/**
 * function update data will update all data from system into data files ../Data/.
 * it will empty the files and update them again from the local system vector if the files can be opened
 */
void System::update_data(){
    update_member_file();
    update_bike_file();
    update_rental_file();
    update_request_to_file();
    update_code_to_file();
}

void System::input_member_list(){ // read all accounts from account file
    member_vector.clear();

    std::ifstream member_file (ACCOUNT_FILE);
    if(!member_file.is_open()){
        std::cerr << "Error: Can't open " << ACCOUNT_FILE << '\n';
        return;
    }

    string str;
    while( getline(member_file, str) ){
        std::vector<string> tokens; 
        tokens = splitStr(str, ';'); // split line into multiple string tokens

        Member* member = new Member(
                                stoi(tokens.at(0)),
                                tokens.at(1), 
                                tokens.at(2), 
                                tokens.at(3), 
                                tokens.at(4), 
                                tokens.at(5),   
                                to_object(tokens.at(6)),
                                stod(tokens.at(7)),
                                tokens.at(8),
                                tokens.at(9),
                                stoi(tokens.at(10)),
                                tokens.at(11),
                                stod(tokens.at(12)) );
        member_vector.push_back(member);
    }
    member_file.close();
}

void System::input_bike_list(){ // read all bikes from bike files
    bike_vector.clear();
    std::ifstream bike_file (MOTORBIKE_FILE);
    if(!bike_file.is_open()){
        std::cerr << "Error: Can't open " << MOTORBIKE_FILE << '\n';
        return;
    }

    string str;
    while( getline(bike_file, str) ){
        std::vector<string> tokens; // split line into multiple string tokens
        tokens = splitStr(str, ';');

        Motorbike* bike = new Motorbike(
                                    stoi(tokens.at(0)),
                                    stoi(tokens.at(1)),
                                    tokens.at(2),
                                    tokens.at(3),
                                    tokens.at(4),
                                    tokens.at(5),
                                    stoi(tokens.at(6)),
                                    tokens.at(7),
                                    tokens.at(8) );
        bike_vector.push_back(bike);
    }
    bike_file.close();
}

void System::link_member_and_bike(){ // connect member and bike through bike_id
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

void System::input_rental_list(){ // read all bikes that are currently available for renting
    rental_list.clear();
    std::ifstream rental_file (RENTAL_FILE);
    if(!rental_file.is_open()){
        std::cerr << "Error: Can't open " << RENTAL_FILE << '\n';
        return;
    }

    string str;
    while( getline(rental_file, str) ){
        std::vector<string> tokens;
        tokens = splitStr(str, ';'); // split line into multiple string tokens

        for(auto bike : bike_vector){
            if(stoi(tokens.at(0)) == bike->bike_id){
                bike->add_rental(stod(tokens.at(1)),
                                 stod(tokens.at(2)),
                                 to_object(tokens.at(3)),
                                 to_object(tokens.at(4)) );

                rental_list.push_back(bike);
                break;
            }
        }  
    }
    rental_file.close();
}

void System::input_request_list(){ // read all requests related data for renting bikes 
    for(auto mem : member_vector){
        mem->request_list.clear();
    }

    std::ifstream request_file (REQUEST_FILE);
    if(!request_file.is_open()){
        std::cerr << "Error: Can't open " << REQUEST_FILE << '\n';
        return;
    }

    string str;
    Request* request;
    while( getline(request_file, str) ){
        std::vector<string> tokens;
        tokens = splitStr(str, ';'); // split line into multiple string tokens
        
        int owner_id = stoi(tokens.at(1));
        int renter_id = stoi(tokens.at(2));
        string status = tokens.at(5);

        for(auto owner : member_vector){
            if(owner_id == owner->id){
                request = new Request ( member_vector.at(renter_id - 1),
                                        to_object(tokens.at(3)),
                                        to_object(tokens.at(4)),
                                        status );

                // assign new request id for request(s) based on the request list
                request->set_request_id(owner->request_list.size() + 1); 
                owner->add_request(request);

                if (status == "ACCEPTED") {
                    for (auto renter : member_vector) {
                        if (renter->id == renter_id) 
                            renter->rented_bike = owner->bike; 
                    }
                }

                break;
            }
        }
    }
    request_file.close();
}

// read all reviews data (bike owner id, bike renter id, score for renter, score for bike) from history files
void System::input_history_review(){ 
    for(auto mem : member_vector){
        mem->reset_review();
        if(mem->bike != nullptr){ mem->bike->reset_review(); }
    }

    std::ifstream history (HISTORY_FILE);
    if(!history.is_open()){
        std::cerr << "Error: Can't open " << HISTORY_FILE << '\n';
        return;
    }

    string str;
    Review* review;
    while( getline(history, str) ){
        std::vector<string> tokens;
        tokens = splitStr(str, ';');
        //owner_id;renter_id;renter_rating; bike_rating;comment
        //1;2;10;9
        int owner_id = stoi(tokens.at(0));
        int renter_id = stoi(tokens.at(1));

        double rating_for_renter = stod(tokens.at(2));
        double rating_for_bike = stod(tokens.at(3));
        string comment = tokens.at(4);

        for(auto bike : bike_vector){
            //found bike to add review
            if(bike->member_id == owner_id){
                review = new Review (rating_for_bike, comment);
                bike->add_review(review);
                break;
            }
        }

        for(auto renter : member_vector){
            if(renter->id == renter_id ){
                review = new Review (rating_for_renter, "None");
                renter->add_review(review);
                break;
            }
        }
    }
    history.close();
}

void System::input_code_list() { // read all codes from the code file
    code_list.empty(); // empty unordered map handle key code 
    string str;
    string key {};
    int value {};

    std::ifstream code_file (CODE_FILE);
    if(!code_file.is_open()){
        std::cerr << "Error: Can't open " << CODE_FILE << '\n';
        return;
    }

    while (getline(code_file, str)) {
        std::vector<string> tokens;
        tokens = splitStr(str, ';'); // split line into multiple string tokens

        code_list.insert({ tokens.at(0), stoi(tokens.at(1)) });
    }    
    code_file.close();
}

void System::update_member_file(){ // update member vector into account file
    std::ofstream update_file (ACCOUNT_FILE);
    if(!update_file.is_open()){
        std::cerr << "Error: Can't update to " << ACCOUNT_FILE << '\n';
        return;
    }
    
    for(auto mem : member_vector) {
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

void System::update_bike_file(){ // update bike vector into bike file
    std::ofstream update_file (MOTORBIKE_FILE);
    if(!update_file.is_open()){
        std::cerr << "Error: Can't update to " << MOTORBIKE_FILE << '\n';
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

void System::update_rental_file(){ // update rental vector (bikes that are currently listed for rental) into rental file 
    std::ofstream update_file (RENTAL_FILE);
    if(!update_file.is_open()){
        std::cerr << "Error: Can't update to " << RENTAL_FILE << '\n';
        return;
    }

    for(auto bike : rental_list) { 
        update_file << bike->bike_id << ";"
                    << bike->point_per_day << ";"
                    << bike->minimum_rating << ";"
                    << bike->start->to_string() << ";"
                    << bike->end->to_string() << '\n';
    }
    update_file.close();
}

void System::update_request_to_file(){ // update request vector of each member into request file
    std::ofstream update_file (REQUEST_FILE);
    if(!update_file.is_open()){
        std::cerr << "Error: Can't update to " << REQUEST_FILE << '\n';
        return;
    }

    for(Member* owner : member_vector){
        int counter = 0; // id counter since this id will changed when the vector is modified
        for(auto request : owner->request_list){ // for every request in request list 
            request->set_request_id(++counter); // add counter by 1 and set it to be the request id

            update_file << request->request_id << ";"
                        << owner->id << ";"
                        << request->renter->id << ";"
                        << request->start->to_string() << ";"
                        << request->end->to_string() << ";"
                        << request->status << '\n';
        }
    }
    update_file.close();
}

void System::update_code_to_file() { // update all key codes to code file 
    std::ofstream code_file (CODE_FILE);
    if(!code_file.is_open()){
        std::cerr << "Error: Can't update to " << CODE_FILE << '\n';
        return;
    }

    for (auto code : code_list) {
        code_file << code.first << ';' << code.second << '\n'; 
    }
    code_file.close();
}

/**
 * System Tool Function
*/

bool System::is_integer(string& str){ // validate if value is int
    std::regex reg { "^[-+]?[0-9]+$" };
    return std::regex_match(str, reg);
}

bool System::is_double(string& str){ // validate if value is double
    std::regex reg { "^(-?)(0|([1-9][0-9]*))(\\.[0-9]+)?$" };
    return std::regex_match(str, reg);
}

// validate if fullname only contains alnum, at least 5 char and at most 20 chars
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
             << "ERROR: `Full name` must contain 5 - 20 characters and `blank_space` only." << '\n'
             << RESET;
        return false;
    }
    return true;
}
 
bool System::validate_phone(string& str){ // validate phone number
    if(str.empty()){
        cout << RED
             << "ERROR: `Phone` is empty." << '\n'
             << RESET;  
        return false;
    }

    std::regex reg { "^(0|84)[0-9]{9}$" }; // leading zeros or 84 only with 10 digits
    string trim_string = trim(str);
  
    if(!std::regex_match(trim_string, reg)){
        cout << RED
             << "ERROR: `Phone` must contain 10 numbers starting with 0 or 84." << '\n'
             << RESET;
        return false;
    }

    return true;
}

bool System::validate_id_type(string& str){ // id type can only be 'id' or 'password'
    if(str.empty()){
        cout << RED
             << "ERROR: `ID TYPE` is empty." << '\n';
        return false;
    }

    std::transform(str.begin(), str.end(), str.begin(), ::tolower); //lowercase the input 
    if(str != "id" && str != "passport"){ //check if the input id type is in the correct format "id" or "passport"
        cout << RED 
             << "ERROR: Invalid format. Input `Id` or `Passport` only." << '\n' //warning if the input is not suitable
             << RESET;
        return false;
    }

    std::transform(str.begin(), str.end(), str.begin(), ::toupper); //uppercase the entered id type if it pass the validate step
    return true;
}

bool System::validate_number(string& str){ //check if an input is numerical
    if(str.empty()){ //print out the error when the input is empty
        cout << RED
             << "ERROR: `Number` is empty." << '\n'
             << RESET;
        return false;
    }

    std::regex reg { "^[a-zA-Z0-9]*$" };
    if(!std::regex_match(str, reg)){ //print out the error when the input contains non-numerical characters or blank space
        cout << RED
             << "ERROR: `Number` must contain no special character including `blank_space`." << '\n'
             << RESET;
        return false;
    }

    return true; //return true when it is a numerical value
}


bool System::validate_date(string& str){ //examine an entered date if it is in the correct format
    if(str.empty()){ //user has entered nothing
        cout << RED
             << "ERROR: `Date` is empty." << '\n'
             << RESET;
        return false;
    }

    std::regex reg { "^([0-2][0-9]|3[0-1])/(0[1-9]|1[0-2])/([0-9]{4})$" };
    if(!std::regex_match(str, reg)){ //check if the input follows the format dd/mm/yyyy (ex: 01/01/2023)
        cout << RED 
             << "ERROR: Invalid format." << '\n'
             << RESET;
        return false;
    }

    int day, month, year;
    sscanf(str.c_str(), "%d/%d/%d", &day, &month, &year); //read and assign associated value from the user's input to day, month and year attribute

    if((month == 4 || month == 6 || month == 9 || month == 11) && (day > 30)){ //announce when the day value of apr, june... is greater than 30
        cout << RED << "ERROR: Invalid `date` input." << '\n' << RESET;
        return false;

    } else if (month == 2){ 
        if( (is_leap_year(year)) && (day > 29) ){ //announce when the day value of Feb is greater than 29 (in case the year is a leap year)
            cout << RED << "ERROR: Invalid `date` input." << '\n' << RESET;
            return false;

        } else if ( (!is_leap_year(year)) && (day > 28) ){ //announce when the day value of Feb is greater than 29 (in case the year is NOT a leap year)
            cout << RED << "ERROR: Invalid `date` input." << '\n' << RESET;
            return false;
        }

    } else if (day > 31){ //day value cannot exceed 31
        cout << RED << "ERROR: Invalid `date` input." << '\n' << RESET;
        return false;
    }

    return true;
}

bool System::is_leap_year(int& year){
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

//validate username input when register with condition 
bool System::validate_username(string& str){ 
    if(str.empty()){
        cout << RED
             << "ERROR: `Username` is empty." << '\n'
             << RESET;
        return false;
    }

    std::regex reg1 { "^[a-zA-Z0-9@.]{4,18}$" };
    std::regex reg2 { "^([^@.]*[@.]?[^@.]*)$" };

    //a username can have either one . or one @
    if(!std::regex_match(str, reg1)){ 
        cout << RED
             << "ERROR: `Username` must contain 4 - 18 characters. No special characters." << '\n'
             << "       `Username` is only available for . and @." << '\n'
             << RESET;
        return false;
    } 

    if (!std::regex_match(str, reg2)){
        cout << RED
             << "ERROR: `Username` contains more than 1 . or @." << '\n'
             << RESET;
        return false;
    }

    for(auto mem : member_vector){ //every username must be unique
        if(str == mem->username){
            cout << RED
                 << "FAILED: `Username` is already taken." << '\n'
                 << RESET;
            return false;
        }
    }

    return true;
}

//validate username input when signing in with condition 
bool System::validate_login_username(string& str){
    if(str.empty()){
        cout << RED
             << "ERROR: `Username` is empty." << '\n'
             << RESET;
        return false;
    }

    for(auto mem : member_vector){ //wrong username
        if(str == mem->username){ return true; }
    }

    cout << RED
         << "FAILED: `Username` doesn't exist." << '\n'
         << RESET;

    return false;
}

//validate the created password in the registration step with condition
bool System::validate_password(string& str){ 
    if(str.empty()){
        cout << RED
             << "ERROR: `Password` is empty." << '\n'
             << RESET;
        return false;
    }

    if( str.length() < 4 || str.find(" ") != std::string::npos ){
        cout << RED
             << "ERROR: `Password` must contains at least 4 characters. No `blank_space`." << '\n'
             << RESET;
        return false;
    }

    return true;
}

//validate the entered password for loging in
bool System::validate_login_password(string& str, string& check){ 
    if(str.empty()){
        cout << RED
             << "ERROR: `Password` is empty." << '\n'
             << RESET;
        return false;
    }

    return str == check;
}

/*
    * Used for registration
    * Send out recommendations if the created password is missing any characteristic to become a strong password
*/
bool System::recommend_password(string& str){
    cout << YELLOW
         << "RECOMMENDATION FOR PASSWORD: " << '\n';

    if (!std::regex_search(str, std::regex("[A-Z]"))) {
        cout << "+ Should contain at least 1 upper_case." << '\n';
    }

    if (!std::regex_search(str, std::regex("[a-z]"))) {
        cout << "+ Should contain at least 1 lower_case." << '\n';
    }

    if (!std::regex_search(str, std::regex("[0-9]"))) {
        cout << "+ Should contain at least 1 number." << '\n';
    }

    if (!std::regex_search(str, std::regex("[!@#$%^&*()]"))) {
        cout << "+ Should contain at least 1 special character ( @, !, $, #, etc. )." << '\n';
    }

    cout << "NOTICE: `Password` is strong enough." << '\n'
         << RESET;

    return true;
}


bool System::validate_model(string& str){ //validate input motorbike models
    if(str.empty()){
        cout << RED
             << "ERROR: `Model` is empty." << '\n'
             << RESET;
        return false;
    }

    std::regex reg { "^[a-zA-Z0-9-]{2,10}$" }; //model can contain letters, numbers and "-"
    if(!std::regex_match(str, reg)){
        cout << RED
             << "ERROR: `Model` must contain 2-10 characters. No special characters." << '\n'
             << "       `Model` is only available for -." << '\n'
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

std::vector<string> System::splitStr(string& str, char ch){ //split a string into multiple string by a specific character
    std::vector<string> tokens;
    std::stringstream ss { str };
    string line;

    while(!ss.eof()){
        getline(ss, line, ch);
        tokens.push_back(line);
    }

    return tokens;
}

string System::trim(string& str){ //remove space at the beginning and end a of a string
    string trim_string;

    for(auto ch : str){
        if(ch != ' '){ trim_string += ch; }
    }

    return trim_string;
}

Date* System::to_object(string& str){ //convert a string to an object of type Date*
    std::vector<string> tokens = splitStr(str, '/');
    Date* converted_date = new Date(
                                stoi(tokens.at(0)), 
                                stoi(tokens.at(1)), 
                                stoi(tokens.at(2)) );

    return converted_date;
}

int System::choice_selection(int a, int b){ //validate input for choice from user
    string input_choice;

    do {
        cout << CYAN 
             << BOLD
             << "> Your choice: "
             << RESET;
        getline(cin, input_choice);

        if( !is_integer(input_choice) ){
            cout << RED 
                 << "ERROR: `Choice` is number ONLY." 
                 << RESET << '\n';

        } else {
            int choice = stoi(input_choice);
            if(choice < a || choice > b){
                cout << RED 
                     << "FAILED: No option " << choice << "."
                     << RESET << '\n';
                
            } else { return choice; }
        }
    } while( true );
}

int System::count_day(Date* start, Date* end){ //parameters are an initial time and a final time
    int day = start->day;
    int month = start->month;
    int year = start->year;
    int day_count = 0;
    int day_of_month;

    if(year > end->year){ 
        return -1; 

    } else if (year == end->year){
        if(month > end->month){
            return -1;

        } else if (month == end->month){
            if(day > end->day){
                return -1;

            } else if (day == end->day){
                return 0;
            }
        }
    }

    while(year <= end->year){ 
        switch(month){
            case 1: case 3: case 5: case 7: case 8: case 10: case 12: //months that have 31 days
                day_of_month = 31;
                break;
            
            case 4: case 6: case 9: case 11: //months that have 30 days
                day_of_month = 30;
                break;

            case 2:
                is_leap_year(year) ? day_of_month = 29 : day_of_month = 28;
             
                break;
        }
        
        //Calculate the number of days from starting day to ending day
        if(month == end->month && year == end->year){ //in the same year and the same months
            day_count == 0 ? (day_count += end->day - start->day + 1) : (day_count += end->day); 
            break;

        } else if (month != end->month) {  //in different months
            day_count == 0 ? (day_count += (day_of_month - start->day + 1)) : (day_count += day_of_month);
        }

        month < 12 ? month++ : month = 1, year++;

    }
    
    return day_count; 
}
/**
 * Feature Function
*/

void System::welcome_screen(){
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

void System::login_menu(){ //display login menu
    input_data();

    cout << BLUE
         << BOLD
         << "------------------------- LOGIN -------------------------\n"
         << "| [1] Guest     [2] Member      [3] Admin      [4] Exit |\n"
         << "---------------------------------------------------------\n"
         << RESET;

    int choice = choice_selection(1, 4); //validate user's choice
    switch(choice){
        case 1: //access as a guest
            system("clear");
            guest_menu();
            break;

        case 2: //access as a member
            system("clear");
            cout << GREEN
                 << BOLD
                 << "---------------------------------------------------------\n"
                 << "|                     MEMBER LOGIN                      |\n" 
                 << "|                 [1] Login as Member                   |\n"
                 << "|                 [2] Return to Menu                    |\n"
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

        case 3: //access as an admin
            system("clear");
            cout << GREEN
                 << BOLD
                 << "---------------------------------------------------------\n"
                 << "|                      ADMIN LOGIN                      |\n" 
                 << "|                 [1] Login as Admin                    |\n"
                 << "|                 [2] Return to Menu                    |\n"
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

        case 4: //exit the program
            update_data();
            cout << CYAN << BOLD
                 << "~~~~~~~~~~ THANKS FOR COMING TO OUR COMMUNITY ~~~~~~~~~~~\n"
                 << RESET;
            exit(0);
    }
}

void System::login_as_admin(){ //access as an admin
    string username, password;
    int count = 4;

    do {
        if(count == 0){
            cout << RED
                 << "LOGIN FAILED: Return to login menu." << '\n'
                 << RESET;

            system("clear");
            login_menu();

        } else if (count != 4){
            cout << RED
                 << "ALERT: Wrong password. " 
                 << BOLD << count << " times left." << '\n'
                 << RESET;
        }

        cout << MAGENTA << "Enter username: " << RESET;
        getline(cin, username);
        count--;
        
    } while ( username != "admin" );

    count = 4;
    do {
        if(count == 0){
            cout << RED
                 << "LOGIN FAILED: Return to login menu." << '\n'
                 << RESET;

            system("clear");
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

    } while ( password != "admin" );

    admin = new Admin();

    system("clear");
    admin_menu();
}

void System::login_as_member(){ //access as a member
    string username, password;
    int count = 4;

    do {
        if(count == 0){
            cout << RED
                 << "LOGIN FAILED: Return to login menu" << '\n'
                 << RESET;

            system("clear");
            login_menu();
        
        } else if (count != 4){
            cout << RED
                 << "ALERT: "
                 << BOLD
                 << count << " times left." << '\n' //wrong input for 4 times
                 << RESET;
        }

        cout << MAGENTA << "Enter username: " << RESET;
        getline(cin, username);
        count--;

    } while ( !validate_login_username(username) );
    
    for(auto mem : member_vector){
        if(username == mem->username){
            current_member = mem;
            break;
        }
    }

    count = 4;
    do {
        if(count == 0){
            cout << RED
                 << "FAILED: `Member` login error." << '\n'
                 << RESET;
            current_member = nullptr;

            system("clear");
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

    } while ( !validate_login_password(password, current_member->password) );
    
    current_bike = current_member->bike;

    system("clear");
    member_menu();
}

// MEMBER
void System::member_menu(){ // show member menu
    cout << GREEN
         << BOLD
         << "Welcome, " << current_member->fullname << " !\n"
         << "--- MEMBER MENU -----------------------------------------\n"
         << "| [1] View personal details                             |\n"
         << "| [2] View your motorbike                               |\n"
         << "| [3] Add a new motorbike                               |\n"
         << "| [4] List bike for renting                             |\n"
         << "| [5] Un-List bike for rental                           |\n"
         << "| [6] Request renting a bike                            |\n"
         << "| [7] View requests from others                         |\n"
         << "| [8] Top up                                            |\n"
         << "| [9] Log out                                           |\n"
         << "---------------------------------------------------------\n"
         << RESET;

    int choice = choice_selection(1, 9);
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
            member_top_up();
            member_menu();
            break;

        case 9:
            current_member = nullptr;
            current_bike = nullptr;
            affordable_bike_list.clear();

            system("clear");
            login_menu();
    }
}

void System::member_view_information(){ // view all information of current member
    cout << YELLOW
         << std::left << std::setw(10) << "ID" 
         << std::left << std::setw(20) << "FULL_NAME" 
         << std::left << std::setw(15) << "PHONE" 
         << std::left << std::setw(15) << "ID_TYPE"
         << std::left << std::setw(15) << "ID_NUMBER"
         << std::left << std::setw(15) << "LICENSE_NO"
         << std::left << std::setw(15) << "EXPIRY_DATE"
         << std::left << std::setw(15) << "CREDITS"
         << std::left << std::setw(15) << "LOCATION"
         << std::left << std::setw(15) << "RATING" << '\n'
         << RESET;
        
        current_member->view_personal_info();
}

void System::member_view_bike_information(){ // view current member's bike info
    if(current_bike == nullptr){
        cout << RED
             << "ERROR: `Bike` not found.\n"
             << "Press [3] to add bike." << '\n'
             << RESET;
        return;

    } else {
        cout << YELLOW
             << std::left << std::setw(15) << "MODEL"
             << std::left << std::setw(15) << "COLOR"
             << std::left << std::setw(15) << "ENGINE_SIZE"
             << std::left << std::setw(20) << "TRANSMISSION_MODE"
             << std::left << std::setw(8)  << "YEAR"
             << std::left << std::setw(17) << "LICENSE_PLATE"
             << std::left << std::setw(10) << "RATING"
             << std::left << std::setw(15) << "DESCRIPTION" << '\n'
             << RESET;

        current_bike->view_bike_info();
    }
}

void System::member_add_bike(){ // add bike of that member
    int id, member_id;
    if(current_bike != nullptr){
        id = current_bike->bike_id;
        cout << RED
             << "ERROR: `Bike` found." << '\n'
             << "ALERT: Do you want to add new one ?" << '\n'
             << RESET;
        
        string confirm;
        bool is_valid_input;
        do {
            cout << MAGENTA << "> Y/N: " << RESET;
            getline(cin, confirm);
        
            is_valid_input =  !(confirm != "Y" && 
                                confirm != "y" && 
                                confirm != "N" && 
                                confirm != "n" );
            if(!is_valid_input){
                cout << RED << "ERROR: `Input` Y or N only." << '\n' << RESET;
            }
        } while ( !is_valid_input );

        if(confirm == "N" || confirm == "n"){
            system("clear");
            member_menu();
        } 

    } else { id = bike_vector.size() + 1; }

    string model, color, engine_size, transmission_mode, license_plate, description;
    string year;

    member_id = current_member->id;

    cout << GREEN
         << BOLD
         << "--- ADDING NEW BIKE ------------------------------\n"
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
                                stoi(year),
                                license_plate,
                                description );
                                
    if (current_bike != nullptr) {
        bike_vector.at(id - 1) = bike;
    } else {
        bike_vector.push_back(bike);
    }
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

    update_data();
    input_data();
}

void System::member_list_rental(){ // list bike available for other to rent
    if(current_bike == nullptr){
        cout << RED
             << "ERROR: `Bike` need to be added first." << '\n'
             << "Press [3] to add bike." << '\n'
             << RESET;
        return;
    }
    
    if(current_bike->status == "AVAILABLE"){
        cout << RED
             << "ERROR: `Bike` is currently AVAILABLE." << '\n'
             << "Press [5] to un-list." << '\n'
             << RESET;
        return;
    }

    cout << GREEN
         << BOLD
         << "--- LISTING MOTORBIKE FOR RENTAL ------------------------\n"
         << RESET;

    string point, rating;
    do {
        cout << MAGENTA << "Enter points/day: " << RESET;
        getline(cin, point);
    } while ( !is_double(point) );

    do {
        cout << MAGENTA << "Minimum rating: " << RESET;
        getline(cin, rating);

        if(stod(rating) > 10){
            cout << RED
                 << "ERROR: `Rating` is between 0 - 10." << '\n'
                 << RESET;
        }
    } while ( !is_double(rating) || stod(rating) > 10);

    string start, end;
    cout << MAGENTA << "+ Rental Period: " << '\n' << RESET;
    do {
        cout << MAGENTA << "Enter start (dd/mm/yyyy): " << RESET;
        getline(cin, start);
    } while( !validate_date(start) ) ;

    int day_count;
    do {
        do {
            cout << MAGENTA << "Enter end (dd/mm/yyyy): " << RESET;
            getline(cin, end);
        } while( !validate_date(end) ) ;

        day_count = count_day(to_object(start), to_object(end));
        if(day_count <= 0){
            cout << RED
                 << "ERROR: `End` is same or earlier than `Start`." << '\n'
                 << RESET;
        }

    } while ( day_count <= 0);

    current_bike->add_rental( stod(point), stod(rating), to_object(start), to_object(end) );
    rental_list.push_back( current_bike );

    cout << BLUE
         << BOLD
         << "---------------------------------------------------------\n"
         << "|                    LIST SUCCESSFULLY                  |\n"
         << "---------------------------------------------------------\n"
         << RESET;

    update_data();
    input_rental_list();
}

void System::member_unlist_rental(){ // unlist the listed bike, block if not have any bikes or a bike is being rented
    if(current_bike == nullptr){
        cout << RED
             << "ERROR: `Bike` need to be added first." << '\n'
             << "Press [3] to add bike." << '\n'
             << RESET;
        return;
    }
    if(current_bike->status == "NOT_AVAILABLE"){
        cout << RED
             << "ERROR: `Bike` need to be listed first." << '\n'
             << "Press [4] to list bike." << '\n'
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

    cout << BLUE
         << BOLD
         << "---------------------------------------------------------\n"
         << "|                  UN-LIST SUCCESSFULLY                 |\n"
         << "---------------------------------------------------------\n"
         << RESET;
        
    update_data();
    input_data();
}

// search for renting by date and location filter
void System::member_search_rent(const string& location, string& start, string& end){
    cout << GREEN
         << BOLD
         << "--- REQUEST FILTER --------------------------------------\n"
         << RESET;

    do {
        cout << MAGENTA << "Enter start (dd/mm/yyyy): " << RESET;
        getline(cin, start);
    } while( !validate_date(start) ) ;

    int day_rent;
    do {
        do {
            cout << MAGENTA << "Enter end (dd/mm/yyyy): " << RESET;
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
         << BOLD
         << "YOUR CURRENT STATUS" << '\n'
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

// view bikes that can be rented at the provided period
void System::member_view_rental_list(const string& search_location, Date* start_date, Date* end_date){
    cout << YELLOW
         << std::left << std::setw(10) << "BIKE_ID"
         << std::left << std::setw(13) << "MODEL"
         << std::left << std::setw(15) << "ENGINE_SIZE"
         << std::left << std::setw(15) << "POINT / DAY"
         << std::left << std::setw(15) << "MIN_RATING"
         << std::left << std::setw(15) << "START_DATE"
         << std::left << std::setw(15) << "END_DATE"
         << std::left << std::setw(12) << "SCORE"
         << std::left << std::setw(15) << "REVIEWS" << '\n'
         << RESET;

    bool is_found = false;
    for(auto rental : rental_list){
        double total_consuming = count_day(start_date, end_date) * rental->point_per_day;

        // filter all bikes not valid
        if (current_bike != nullptr) { 
            if(rental->bike_id == current_bike->bike_id){
                continue;
            }
        }
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

        // if not meet any condition above
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
                 << std::left << std::setw(12) << rental->motorbike_score;
        
            for(int i = 0; i < rental->renter_review.size(); i++){
                if(i == 0){
                    cout << std::left << std::setw(15) << rental->renter_review.at(i)->comment << '\n';
                } else {
                    cout << std::setw(110) << " "                              
                         << rental->renter_review.at(i)->comment << '\n';
                }
            }
            affordable_bike_list.push_back( rental );
        }
    }
    
    if( !is_found ){
        cout << RED
             << "ERROR: No `Motorbike` is available with filter." << '\n'
             << RESET;

        member_menu();
    }
    cout << '\n';
}

void System::member_request_rent(){ // send request to rent bike 
    if(current_member->rented_bike != nullptr){
        cout << RED
             << "ERROR: `Member` can only occupy 1 motorbike." << '\n'
             << RESET;

        member_menu();
    }

    string location = current_member->location;
    string start, end;
    member_search_rent(location, start, end);
    
    string input;
    Motorbike* found_bike;
    
    bool is_found = false;
    do {
        do {
            cout << MAGENTA << "Enter `ID` to rent (0 to EXIT): " << RESET;
            getline(cin, input);

            if(input == "0"){
                member_menu();
            }
        } while ( !is_integer(input) );

        for(auto bike : affordable_bike_list){
            if(bike->bike_id == stoi(input)){
                found_bike = bike;
                is_found = true;
                break;
            }
        }
        if( !is_found ){
            cout << RED 
                 << "ERROR: `Motorbike` not found." << '\n'
                 << RESET;
        }
    } while ( !is_found );

    found_bike->owner->add_request( new Request ( current_member, to_object(start), to_object(end) ));
    affordable_bike_list.clear();
    
    cout << YELLOW
         << BOLD
         << "---------------------------------------------------------\n"
         << "|                    REQUEST COMPLETED                  |\n"
         << "---------------------------------------------------------\n"
         << RESET;
         
    update_data();
    input_data();
}   
    
void System::member_view_request(){ // view all requests of current member's bike 
    if(current_member->request_list.size() == 0){ // if no request
        cout << RED
             << "ERROR: There is no `Request` for your bike." << '\n'
             << RESET;
        return;

    } else {
        cout << GREEN
             << BOLD
             << "--- CURRENT REQUESTS ------------------------------------\n"
             << RESET;
        current_member->view_request();
    }

    string input;
    int chosen_id;
    bool is_found { false };
    Date* start;
    Date* end;
    double total;
    std::vector<Request*> tmp;
    int count {};

    do {
        do {
            cout << MAGENTA << "Enter choice to accept (0 to EXIT): " << RESET;
            getline(cin, input);

            if(input == "0"){
                member_menu();
            } 
        } while ( !is_integer(input) );

        chosen_id = stoi( input );
    
        for(auto request : current_member->request_list){
            if(chosen_id == request->request_id){
                is_found = true;
                
                if (request->status == "ACCEPTED") {
                    cout << RED
                         << "ERROR: You have accepted this request." << '\n'
                         << RESET;
                    is_found = false;

                } else if (request->renter->rented_bike != nullptr){
                    if(request->renter->rented_bike == current_bike){
                        cout << RED
                             << "ERROR: `Renter` already rented your bike." << '\n'
                             << RESET;
                    } else {
                        cout << RED
                             << "ERROR: `Renter` already occupied another bike." << '\n'
                             << RESET;
                    }
                    cout << RED
                         << "You have to wait until the rental finished to accept this." << '\n'
                         << RESET;

                    is_found = false;
                    
                } else {
                    start = request->start;
                    end = request->end;

                    for(auto target : current_member->request_list){
                        if(target->status == "ACCEPTED"){
                            if(count_day(target->start, start) >= 0 && count_day(end, target->end) >= 0){
                                is_found = false;
                            }
                            if( count_day(target->start, start) >= 0 && 
                                count_day(target->end, end) >= 0 &&
                                count_day(start, target->end) >= 0){
                                is_found = false;
                            }
                            if( count_day(start, target->start) >= 0 && 
                                count_day(target->start, end) >= 0 &&
                                count_day(end, target->end) >= 0 ){
                                is_found = false;
                            }
                            if( count_day(start, target->start) >= 0 && count_day(target->end, end) >= 0){
                                is_found = false;
                            }
                        }
                    }
                    if(!is_found){
                        cout << RED
                             << "ERROR: `Bike` is being rented at this period." << '\n'
                             << RESET;
                        is_found = false;
                        current_member->request_list.erase(current_member->request_list.begin() + chosen_id - 1);

                        cout << GREEN
                             << BOLD
                             << "--- CURRENT REQUESTS ------------------------------------\n"
                             << RESET;
                        current_member->view_request();

                    } else {
                        request->get_accepted();

                        update_data();
                        tmp.push_back(request);
                    }
                }
                break;
            }
        }
    } while ( !is_found );
    

    bool is_declined;
    Request* target;

    for(int i = 0; i < current_member->request_list.size(); i++){
        is_declined = false;
        target = current_member->request_list.at(i);

        if(count_day(target->start, start) >= 0 && count_day(end, target->end) >= 0){
            is_declined = true;
        }
        if( count_day(target->start, start) >= 0 && 
            count_day(target->end, end) >= 0 &&
            count_day(start, target->end) >= 0){
            is_declined = true;
        }
        if( count_day(start, target->start) >= 0 && 
            count_day(target->start, end) >= 0 &&
            count_day(end, target->end) >= 0 ){
            is_declined = true;
        }
        if( count_day(start, target->start) >= 0 && count_day(target->end, end) >= 0){
            is_declined = true;
        }

        if(!is_declined){
            tmp.push_back(target);
        }
    }
    current_member->request_list.clear();
    current_member->request_list = tmp;

    for (auto request : current_member->request_list) {
        if(chosen_id == request->request_id){
            request->renter->rented_bike = current_bike;
            total = count_day(start, end) * current_bike->point_per_day;

            request->renter->use_credit_point( total );
            current_member->earn_credit_point( total ) ;
            break;
        } 
    }

    update_data();  
    input_request_list();

    member_view_request();
}

void System::member_top_up() { // top up to member account
    string amount, code_input;
    string data;

    do {
        cout << MAGENTA << "Enter value: " << RESET;
        getline(cin, amount);
    } while ( !is_double(amount) );
    
    for(auto code : code_list){
        if(stod(amount) == code.second){
            data = code.first;
            break;
        }
    }

    cout << GREEN
         << BOLD
         << "YOUR CODE: " << data << '\n'
         << RESET;

    bool is_valid;
    do {
        cout << MAGENTA << "Enter code to top-up: " << RESET;
        getline(cin, code_input);
        is_valid = (code_input == data);

        if( !is_valid ){
            cout << RED
                 << "ERROR: Invalid input." << '\n'
                 << RESET;
        }

    } while ( !is_valid );

    for (auto code : code_list) {
        if (data == code.first) {
            // cout << code.first << ";" << code.second << '\n';
            current_member->earn_credit_point(code.second);
            code_list.erase(code.first);
            break;
        }
    }
    update_data();
    input_data();
}

// GUEST
void System::guest_menu(){
    cout << GREEN
         << BOLD
         << "~~~~~~~~~~~~~~~ WELCOME TO OUR COMMUNITY ~~~~~~~~~~~~~~~~\n"
         << "--- GUEST MENU ------------------------------------------\n"
         << "| [1] View all motorbikes                               |\n"
         << "| [2] Member registration                               |\n"
         << "| [3] Exit                                              |\n"
         << "---------------------------------------------------------\n"
         << RESET;

    int choice = choice_selection(1, 3); // option from 1 - 3, if not in range, print out error message
    switch(choice){
        case 1:
            guest_view_bike();
            guest_menu();
            break;

        case 2:
            guest_registration();
            login_menu();
            break;

        case 3:
            system("clear");
            login_menu();
    }
}

void System::guest_view_bike(){ // guest can view all bikes info except for their reviews
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

void System::guest_registration(){ // register to be a member of the system
    int id, bike_id;
    string username, fullname, phone;
    string id_type, id_number, license_number, expiry_date, password;
    double credit_point, renting_score;

    id = member_vector.size() + 1;
    cout << GREEN
         << BOLD
         << "--- MEMBER REGISTRATION ---------------------------------\n"
         << RESET;

    do {
        cout << MAGENTA << "Enter full-name: " << RESET;
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
        cout << MAGENTA << "Expiry-date (dd/mm/yyyy): " << RESET;
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
    // renting_score = 0;

    cout << MAGENTA
         << "LOCATION:  [1] SAIGON   [2] HANOI" << '\n'
         << RESET;
    
    int choice = choice_selection(1, 2);
    string location = LOCATIONS[choice - 1]; // index = choice - 1

    cout << YELLOW
         << BOLD
         << "---------------------------------------------------------\n"
         << "|                 REGISTRATION COMPLETED                |\n"
         << "|            20 points is added to your account         |\n"
         << "---------------------------------------------------------\n"
         << RESET;

    Member* new_member = new Member(id, fullname, phone, id_type, id_number, license_number, 
                                    to_object(expiry_date), credit_point, username, password, 
                                    bike_id, location);

    member_vector.push_back( new_member ); // add new member to the member list of system
    cout << '\n';

    update_member_file(); // update member vector to file
    input_data(); // read all data 
}

// ADMIN
void System::admin_menu(){
    cout << GREEN
         << BOLD
         << "--- ADMIN DASHBOARD -------------------------------------\n"
         << "| [1] View all members                                  |\n"
         << "| [2] View all motorbikes                               |\n"
         << "| [3] Generate code                                     |\n"
         << "| [4] EXIT                                              |\n"
         << "---------------------------------------------------------\n"
         << RESET;

    int choice = choice_selection(1, 4);
    switch(choice){
        case 1:
            admin_view_all_members(); // call view all members function of admin
            admin_menu();
            break;

        case 2:
            admin_view_all_bikes(); // call view all bikes function of admin
            admin_menu();
            break;

        case 3:
            admin_generate_code(); // call auto generated code of admin
            admin_menu();
            break;

        case 4:
            system("clear");
            login_menu();
    }
}

void System::admin_view_all_members(){ // view all member in the system
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

void System::admin_view_all_bikes(){ // view all bike info in the system
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

void System::admin_generate_code() { // code generating by admin
    string code_value, number_of_code;

    // handle code value input
    do {
        cout << MAGENTA << "Enter code value: " << RESET;
        getline(cin, code_value);
        if( !is_integer(code_value) ){
            cout << RED
                 << "ERROR: `Value` is integer." << '\n'
                 << RESET;
        } else { break; }

    } while (true);

    // handle number of code generated
    do {
        cout << MAGENTA << "Amount of code: " << RESET;
        getline(cin , number_of_code);
        if( !is_integer(number_of_code) || stoi(number_of_code) >= 1){
            cout << RED
                 << "ERROR: `Value` is integer." << '\n'
                 << RESET;
        } else { break; }
    } while ( true );

    std::unordered_map<string, int> generated;
    generated = this->admin->code_generator(stoi(code_value), stoi(number_of_code));
    code_list.insert(generated.begin(), generated.end());

    update_data();
    input_data();
}