#include "Lion.h"
#include <iostream>

Lion::Lion(const std::string& name, int age, double weight)
    : Animal(name, age, weight), 
      Mammal(name, age, weight, "Kratko, smeđe krzno s grivom kod mužjaka") {
    std::cout << "Dodan lav: " << name << std::endl;
}

std::string Lion::getSpecies() const {
    return "Lav (Panthera leo)";
}

double Lion::getDailyFood() const {
    return weight * 0.06;
}