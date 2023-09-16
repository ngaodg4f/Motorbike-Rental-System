#include <iostream>
#include <iomanip>
using std::cout, std::string;

int main(){
    cout
         << std::left << std::setw(10) << "BIKE_ID"
         << std::left << std::setw(13) << "MODEL"
         << std::left << std::setw(15) << "ENGINE_SIZE"
         << std::left << std::setw(15) << "POINT / DAY"
         << std::left << std::setw(15) << "MIN_RATING"
         << std::left << std::setw(15) << "START_DATE"
         << std::left << std::setw(15) << "END_DATE"
         << std::left << std::setw(20) << "DESCRIPTION"
         << std::left << std::setw(15) << "REVIEWS" << '\n';
    for(int i = 0 ; i < 5; i++){
        cout << std::right << std::setw(119) << i << '\n';
    }
}