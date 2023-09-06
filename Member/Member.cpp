#include "Member.h"
using std::cout, std::string;
/* 
    No Exception Handling 
    No Getter
*/
Member::Member(string username = " ", string password = " ")
: username(username), password(password) {}

Member::Member(
            int id,
            std::string fullname,
            std::string phone,
            string id_type,
            string id_number,
            std::string license_number,
            Date* expiry_date,
            double credit_point,
            std::string username,
            std::string password,
            int bike_id,
            string location): 
        id(id),
        fullname(fullname),
        phone(phone),
        id_type(id_type),
        id_number(id_number),
        license_number(license_number),
        expiry_date(expiry_date),
        credit_point(credit_point),
        username(username),
        password(password),
        bike_id(bike_id),
        location(location) {}