#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "Member/Member.h"

#define ACCOUNT_FILE "Data/Account.txt"
using std::cout, std::cin, std::string;

std::vector<Member*> member_vector;

std::vector<string> splitStr(string& str, char ch){
    std::vector<string> data_list;
    std::stringstream ss;
    string tokens;

    while(!ss.eof()){
        getline(ss, tokens, ch);
        data_list.push_back(tokens);
    }

    return data_list;
}

Date to_object(string& str){
    std::stringstream ss;
    int day, month, year;

    string input;
    char slash;
    ss >> day >> slash >> month >> slash >> year;

    return Date (day, month, year);
}

void input_member_list(){
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
}

void update_member_file(){
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
                    << mem->get_expiry_date().to_string() << ";"
                    << std::to_string(mem->get_credit_point()) << ";"
                    << mem->get_username() << ";"
                    << mem->get_password() << ";"
                    << std::to_string(mem->get_bike_id()) << '\n';
    }

    update_file.close();
}

void guest_to_member(){
    int id, credit_point, bike_id;
    string username, fullname, phone;
    string id_type, id_number, license_number, expiry_date, password;
    
    id = member_vector.size();
    
    cout << "- Fullname: ";
    getline(cin >> std::ws, fullname);
    cout << "- Phone: ";
    getline(cin >> std::ws, phone);
    cout << "ID Type: ";
    getline(cin >> std::ws, id_type);
    cout << "ID Number: ";
    getline(cin >> std::ws, id_number);
    cout << "License Number: ";
    getline(cin >> std::ws, license_number);
    cout << "- Expiry Date: ";
    getline(cin >> std::ws, expiry_date);
    cout << "- Usename: ";
    getline(cin >> std::ws, username);
    cout << "Password: ";
    getline(cin >> std::ws, password);
    
    credit_point = 20;
    bike_id = 0;
    
    Member* new_member = new Member(id, fullname, phone, id_type, id_number, license_number, 
                                    to_object(expiry_date), credit_point, username, password, bike_id);

    member_vector.push_back(new_member);
}

int main(){
    // g++ Member/Member.cpp Date/Date.cpp test.cpp -o a.out
    input_member_list();
    for(auto e : member_vector){
        cout << "ID " << e->get_id() << " saved" << '\n';
    }
}