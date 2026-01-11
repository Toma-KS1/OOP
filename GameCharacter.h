#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include <string>

class GameCharacter {
protected:
    std::string name;
    int health;
    bool alive;
    
public:
    GameCharacter(const std::string& name, int health);
    virtual ~GameCharacter();
    
    virtual void displayStatus() const = 0;
    virtual void specialAbility() = 0;
    
    void takeDamage(int damage);

    bool isAlive() const { return alive; }
    int getHealth() const { return health; }
    std::string getName() const { return name; }
};

#endif