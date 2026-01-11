#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <memory>

class Animal {
protected:
    std::string name;
    int age;
    double weight;
    
    Animal(const std::string& name, int age, double weight);
    
public:
    virtual ~Animal() = default;
    
    virtual std::string getSpecies() const = 0;
    virtual double getDailyFood() const = 0;
    virtual std::string getName() const final;
    
    virtual int getAge() const;
    virtual double getWeight() const;
    
    static void validateAnimalData(const std::string& name, int age, double weight);
};

#endif