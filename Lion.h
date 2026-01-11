#ifndef LION_H
#define LION_H

#include "Mammal.h"
#include <string>

class Lion : public Mammal {
public:
    Lion(const std::string& name, int age, double weight);
    
    virtual ~Lion() = default;
    
    std::string getSpecies() const override;
    double getDailyFood() const override;
};

#endif