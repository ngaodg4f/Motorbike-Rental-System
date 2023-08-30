#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
using std::cout, std::cin, std::string;

/*
EEET2482/COSC2082 ASSIGNMENT
MOTORBIKE RENTAL APPLICATION
Instructor: Dr. Ling Huo Chong
Group: Group No.
sXXXXXXX, Student Name
sXXXXXXX, Student Name
sXXXXXXX, Student Name
sXXXXXXX, Student Name
Use the app as 1. Guest
Enter your choice: 2
Enter username:
...
This is your menu: 0. Exit
1. View Information 2. ...
Enter your choice: 1
...
2. Member
*/

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

    cout << "> Your choice: ";
}

#endif