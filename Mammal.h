#ifndef MAMMAL_H
#define MAMMAL_H

#include "Animal.h"
#include <string>

class Mammal : public virtual Animal {
protected:
    std::string furType;
    
public:
    Mammal(const std::string& name, int age, double weight, 
           const std::string& furType);
    
    virtual ~Mammal() = default;
    
    std::string getFurType() const;
    
};

#endif