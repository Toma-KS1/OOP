#ifndef SEATURTLE_H
#define SEATURTLE_H

#include "Aquatic.h"
#include <string>

class SeaTurtle : public Aquatic {
public:
    SeaTurtle(const std::string& name, int age, double weight);
    
    virtual ~SeaTurtle() = default;
    
    std::string getSpecies() const override;
    double getDailyFood() const override;
};

#endif