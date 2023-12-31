#ifndef REVIEW_H
#define REVIEW_H

#include <iostream>

class Review {
    private:
        double score;
        std::string comment;

    public:
        Review(double, std::string);

        double get_score();

        void set_score();

        std::string get_comment();

        friend class System;
        friend class Motorbike;
        friend class Member;
};

#endif