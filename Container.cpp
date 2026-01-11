#include "container.h"
#include <iostream>
#include <utility>
#include <stdexcept>

Container::Container(std::size_t inicijalni_kapacitet) 
    : niz(nullptr), velicina(0), kapacitet(inicijalni_kapacitet) {
    
    if (kapacitet > 0) {
        niz = new int[kapacitet];
    }
    std::cout << "Osnovni konstruktor pozvan. Kapaciteta: " << kapacitet << std::endl;
}

Container::Container(const Container& drugi) 
    : velicina(drugi.velicina), kapacitet(drugi.kapacitet) {
    
    if (kapacitet > 0) {
        niz = new int[kapacitet];
        for (std::size_t i = 0; i < velicina; i++) {
            niz[i] = drugi.niz[i];
        }
    } else {
        niz = nullptr;
    }
    std::cout << "Kopija konstruktora pozvana. Velicina: " << velicina << std::endl;
}

Container::Container(Container&& drugi) noexcept 
    : niz(drugi.niz), velicina(drugi.velicina), kapacitet(drugi.kapacitet) {
    
    drugi.niz = nullptr;
    drugi.velicina = 0;
    drugi.kapacitet = 0;
    std::cout << "Micanje konstruktora pozvano. Velicina: " << velicina << std::endl;
}

Container::~Container() {
    delete[] niz;
    std::cout << "Destruktor pozvan. Velicina je bila: " << velicina << std::endl;
}

Container& Container::operator=(const Container& drugi) {
    
    if (this != &drugi) {
        delete[] niz;
        
        velicina = drugi.velicina;
        kapacitet = drugi.kapacitet;

        if (kapacitet > 0) {
            niz = new int[kapacitet];
            for (std::size_t i = 0; i < velicina; i++) {
                niz[i] = drugi.niz[i];
            }
        } else {
            niz = nullptr;
        }
    }
    return *this;
}

Container& Container::operator=(Container&& drugi) noexcept {
    
    if (this != &drugi) {  
        delete[] niz;
        
        niz = drugi.niz;
        velicina = drugi.velicina;
        kapacitet = drugi.kapacitet;

        drugi.niz = nullptr;
        drugi.velicina = 0;
        drugi.kapacitet = 0;
    }
    return *this;
}

void Container::push_back(int value) {
    if (velicina >= kapacitet) {
        std::size_t novi_kapacitet = (kapacitet == 0) ? 1 : kapacitet * 2;
        realociraj(novi_kapacitet);
        std::cout << "Realociran na kapacitet: " << kapacitet << std::endl;
    }
    
    niz[velicina] = value;
    velicina++;
}

std::size_t Container::size() const {
    return velicina;
}

std::size_t Container::capacity() const {
    return kapacitet;
}

const int& Container::at(std::size_t index) const {
    if (index >= velicina) {
        throw std::out_of_range("Index van opsega");
    }
    return niz[index];
}

void Container::clear() {
    velicina = 0;
}

void Container::print() const {
    std::cout << "Container [velicina=" << velicina << ", kapacitet=" << kapacitet << "]: ";
    if (velicina == 0) {
        std::cout << "prazan";
    } else {
        std::cout << "{ ";
        for (std::size_t i = 0; i < velicina; i++) {
            std::cout << niz[i];
            if (i < velicina - 1) {
                std::cout << ", ";
            }
        }
        std::cout << " }";
    }
    std::cout << std::endl;
}

void Container::realociraj(std::size_t novi_kapacitet) {
    int* novi_niz = new int[novi_kapacitet];
    
    for (std::size_t i = 0; i < velicina; i++) {
        novi_niz[i] = niz[i];
    }

    delete[] niz;
    niz = novi_niz;
    kapacitet = novi_kapacitet;
}