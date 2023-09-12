#include "Request.h"

using std::cout, std::string;

Request::Request(Member* renter, Date* start, Date* end)
: renter(renter), start(start), end(end) {}