#include <iostream>
#include <memory>
#include <vector>
#include "Lion.h"
#include "SeaTurtle.h"
#include "Dolphin.h"

void displayAnimalInfo(const Animal& animal) {
    std::cout << "\nŽivotinje:" << std::endl;
    std::cout << "Ime: " << animal.getName() << std::endl;
    std::cout << "Vrsta: " << animal.getSpecies() << std::endl;
    std::cout << "Dnevna hrana: " << animal.getDailyFood() << " kg" << std::endl;
}

int main() {
    std::vector<std::unique_ptr<Animal>> zooAnimals;
    
    try {
        std::cout << "Dodavanje životina..." << std::endl;
        
        auto leo = std::make_unique<Lion>("Leo", 5, 190.0);
        auto nesto = std::make_unique<SeaTurtle>("Nesto", 50, 180.0);
        auto nesto2 = std::make_unique<Dolphin>("Nesto2", 10, 200.0);
        
        zooAnimals.push_back(std::move(leo));
        zooAnimals.push_back(std::move(nesto));
        zooAnimals.push_back(std::move(nesto2));
        
        std::cout << "\n\nZOO:" << std::endl;
        for (const auto& animal : zooAnimals) {
            displayAnimalInfo(*animal);
        }
        
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error creating animal: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}