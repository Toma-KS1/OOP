#ifndef GNOME_H
#define GNOME_H

#include "Enemy.h"

class Gnome : public Enemy {
public:
    Gnome(const std::string& name);
    ~Gnome();
    
    void displayStatus() const override;
    void specialAbility() override;
    void attackPlayer(Player* target) override;
};

#endif