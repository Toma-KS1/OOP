#include "Mammal.h"
#include <iostream>

Mammal::Mammal(const std::string& name, int age, double weight, 
               const std::string& furType)
    : Animal(name, age, weight), furType(furType) {
    std::cout << "Stvoren sisavac s vrstom krzna: " << furType << std::endl;
}

std::string Mammal::getFurType() const {
    return furType;
}