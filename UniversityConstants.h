#ifndef UNIVERSITYCONSTANTS_H
#define UNIVERSITYCONSTANTS_H

#include <iostream>

struct UniversityConstants {
    static const int MAX_ECTS_PER_YEAR = 60;
    static const int REQUIRED_ECTS_PER_YEAR = 45;
    
    static void print_university_rules();
};

#endif