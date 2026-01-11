#include "Dolphin.h"
#include <iostream>

Dolphin::Dolphin(const std::string& name, int age, double weight)
    : Animal(name, age, weight),
      Mammal(name, age, weight, "Glatka, gumenasta koža"),
      Aquatic(name, age, weight, 300.0) {
    std::cout << "Dodan dupin: " << name << std::endl;
}

std::string Dolphin::getSpecies() const {
    return "Dupin (Delphinidae)";
}

double Dolphin::getDailyFood() const {
    return weight * 0.05;
}