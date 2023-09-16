#include "Request.h"

using std::cout, std::string;

Request::Request(Member* renter, Date* start, Date* end)
: renter(renter), start(start), end(end) {
    this->status = "WAITING";
}

Request::Request(Member* renter, Date* start, Date* end, string status)
: renter(renter), start(start), end(end), status(status) {}

void Request::view_request(){
    cout << YELLOW
         << std::left << std::setw(10) << renter->id
         << std::left << std::setw(20) << renter->fullname
         << std::left << std::setw(15) << renter->credit_point
         << std::left << std::setw(15) << start->to_string()
         << std::left << std::setw(15) << end->to_string()
         << std::left << std::setw(15) << renter->renting_score << '\n'
         << RESET;
}

void Request::get_accepted(){
    this->status = "ACCEPTED";
}