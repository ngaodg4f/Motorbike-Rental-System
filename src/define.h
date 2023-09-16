#ifndef DEFINE_H
#define DEFINE_H

#include <iostream>
#define RESET       "\033[0m"       /* Reset */
#define BOLD        "\033[1m"       /* Bold */
#define UNDERLINE   "\033[4m"       /* Underline */
#define HIDDEN      "\033[8m"       /* Hidden */

#define BLACK       "\033[30m"      /* Black */
#define RED         "\033[31m"      /* Red */
#define GREEN       "\033[32m"      /* Green */
#define YELLOW      "\033[33m"      /* Yellow */
#define BLUE        "\033[34m"      /* Blue */
#define MAGENTA     "\033[35m"      /* Magenta */
#define CYAN        "\033[36m"      /* Cyan */
#define WHITE       "\033[37m"      /* White */

const std::string LOCATIONS[2] = { "SAIGON", "HANOI" };
const int INITIAL_CREDITS = 20;

#endif