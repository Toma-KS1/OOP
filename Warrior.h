#ifndef WARRIOR_H
#define WARRIOR_H

#include "Player.h"

class Warrior : public Player {
private:
    bool shieldActive;
    
public:
    Warrior(const std::string& name);
    ~Warrior();
    
    void displayStatus() const override;
    void specialAbility() override;
    void attackEnemy(Enemy* target) override;
};

#endif