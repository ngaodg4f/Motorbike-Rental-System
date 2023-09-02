#include "Login.h"
using std::cout, std::cin;

void welcome_screen(){
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
    cout << "1. Guest\t2. Member\t3. Admin" << '\n'; 
    user_choice();
}


void user_choice(){
    int choice;
    while(true){
        cout << "> Your choice: ";
        cin >> choice;
        if(choice < 1 || choice > 3){
            std::cerr << "Error with option " << choice << '\n';
        } else {
            break;
        }
    }

    switch(choice){
        case 1:
            cout << "LOGIN AS GUEST" << '\n';
            guest_login();
            break;

        case 2:
            cout << "LOGIN AS MEMBER" << '\n';
            break;

        case 3:
            cout << "LOGIN AS ADMIN" << '\n';
    }
}

void guest_login(){
    int choice;
    cout << "LOGIN AS GUEST" << '\n';
    cout << "-----MENU-----" << '\n';
    cout << "1. View all motorbikes" << '\n';
    cout << "2. Member registration" << '\n';

    while(true){
        cout << "> Your choice: ";
        cin >> choice;
        if(choice < 1 || choice > 2){
            std::cerr << "Error with option " << choice << '\n';
        } else {
            break;
        }
    }

    switch(choice){
        case 1:
            
    }
}