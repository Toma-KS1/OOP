#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

class Boss : public Enemy {
public:
    Boss(const std::string& name);
    ~Boss();
    
    void displayStatus() const override;
    void specialAbility() override;
    void attackPlayer(Player* target) override;
};

#endif