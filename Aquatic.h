#ifndef AQUATIC_H
#define AQUATIC_H

#include "Animal.h"
#include <string>

class Aquatic : public virtual Animal {
protected:
    double maxDiveDepth;
    
public:
    Aquatic(const std::string& name, int age, double weight, 
            double maxDiveDepth);
    
    virtual ~Aquatic() = default;
    
    double getMaxDiveDepth() const;
    
};

#endif