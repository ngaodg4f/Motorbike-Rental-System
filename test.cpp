#include <iostream>
#include <vector> 
using std::cout;
int main(){
    std::vector<int> nums = {1, 2, 3};
    for (auto it = nums.begin(); it != nums.end();) {
        if (*it == 2) {
            it = nums.erase(it); // Erase the element and advance the iterator
        } else {
            ++it; // Move to the next element
        }
    }
    for(auto i : nums){
        cout << i << '\n';
    }
}