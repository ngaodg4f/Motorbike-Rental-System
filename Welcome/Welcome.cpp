#include "Welcome.h"
using std::cout, std::cin;

void welcomeScreen(){
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
    userChoice();
}

void userChoice(){
    int choice;
    while(true){
        cout << "> Your choice: ";
        cin >> choice;
        if(choice < 0 || choice > 3){
            std::cerr << "Error with option " << choice << '\n';
        } else {
            break;
        }
    }

    switch(choice){
        case 1:
            cout << "LOGIN AS GUEST" << '\n';
            break;

        case 2:
            cout << "LOGIN AS MEMBER" << '\n';
            break;

        case 3:
            cout << "LOGIN AS ADMIN" << '\n';
    }
}