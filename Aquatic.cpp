#include "Aquatic.h"
#include <iostream>

Aquatic::Aquatic(const std::string& name, int age, double weight, 
                 double maxDiveDepth)
    : Animal(name, age, weight), maxDiveDepth(maxDiveDepth) {
    std::cout << "Stvorena vodena životinja s maksimalnom dubinom ronjenja: " 
              << maxDiveDepth << " metara" << std::endl;
}

double Aquatic::getMaxDiveDepth() const {
    return maxDiveDepth;
}