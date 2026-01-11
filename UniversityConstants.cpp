#include "UniversityConstants.h"
#include <iostream>

void UniversityConstants::print_university_rules() {
    std::cout << "\nPRAVILA\n";
    std::cout << "1. Maksimalno ECTS bodova po godini: " 
              << MAX_ECTS_PER_YEAR << "\n";
    std::cout << "2. Obavezan broj ECTS bodova za upis u narednu godinu: " 
              << REQUIRED_ECTS_PER_YEAR << "\n";
}