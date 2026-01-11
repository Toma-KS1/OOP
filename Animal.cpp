#include "Animal.h"
#include <stdexcept>
#include <iostream>

Animal::Animal(const std::string& name, int age, double weight) 
    : name(name), age(age), weight(weight) {
    validateAnimalData(name, age, weight);
}

void Animal::validateAnimalData(const std::string& name, int age, double weight) {
    if (name.empty()) {
        throw std::invalid_argument("Ime životinje ne može biti prazno");
    }
    if (age < 0) {
        throw std::invalid_argument("Dob životinje ne može biti negativna");
    }
    if (weight <= 0) {
        throw std::invalid_argument("Težina životinje mora biti veća od 0");
    }
}

std::string Animal::getName() const {
    return name;
}

int Animal::getAge() const {
    return age;
}

double Animal::getWeight() const {
    return weight;
}