#include "SeaTurtle.h"
#include <iostream>

SeaTurtle::SeaTurtle(const std::string& name, int age, double weight)
    : Animal(name, age, weight), 
      Aquatic(name, age, weight, 200.0) {
    std::cout << "Dodana morska kornjača: " << name << std::endl;
}

std::string SeaTurtle::getSpecies() const {
    return "Morska kornjača (Chelonioidea)";
}

double SeaTurtle::getDailyFood() const {
    return weight * 0.03;
}