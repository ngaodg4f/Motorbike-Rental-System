# Motorbike-Renting-System
 This is a course project from RMIT University Vietnam

# Link to run the application

g++ ../Motorbike/Motorbike.cpp ../Member/Member.cpp ../Date/Date.cpp ../Review/Review.cpp ../Admin/Admin.cpp System.cpp -o a.out

g++ ./Motorbike/Motorbike.cpp ./Member/Member.cpp ./Date/Date.cpp ./Review/Review.cpp ./Admin/Admin.cpp ./Request/Request.cpp ./System/System.cpp main.cpp -o a.out

REMINDER: 
/*
    for (int; int < size(); i++ ){
        // get the view of choice and for to choose
        cout << i; 
    }
    int put choice (0 to exit): 
    input --> run cai do;
    unreview.at(i).get_new_review()...
    getline()... --> input score, comment
    pushback --> vector tuong ung. erase(begin + i);
    rate_function();
    
    bam 0 --> update_file();
*/

/*
Bike dang state available --> k the add (override) bike
*/