#include "Review.h"
using std::cout, std::string;

Review::Review(double score = 0, string comment = "")
: score(score), comment(comment){}

double Review::get_score() { return score; }

void Review::set_score() { this->score = score; }