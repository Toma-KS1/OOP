#include "Boss.h"
#include "Player.h"
#include <iostream>

Boss::Boss(const std::string& name) 
    : Enemy(name, 300, 8) {}

Boss::~Boss() {
    std::cout << "Boss " << name << " has been vanquished." << std::endl;
}

void Boss::displayStatus() const {
    std::cout << "Boss " << name << " | Health: " << health 
              << " | Difficulty: " << difficulty << "/10" << std::endl;
}

void Boss::specialAbility() {
    if (alive) {
        std::cout << name << " uses regen to gain 50 health!" << std::endl;
        int newHealth = health + 50;
        if (newHealth > 300) {
            newHealth = 300;
            std::cout << name << " is at full health (300)." << std::endl;
        }
        health = newHealth;
    }
}

void Boss::attackPlayer(Player* target) {
    if (!alive) {
        std::cout << name << " is dead and cannot attack!" << std::endl;
        return;
    }
    
    if (target && target->isAlive()) {
        std::cout << name << " breaks the ground under player!" << std::endl;
        int damage = 10 * difficulty;
        
        if (target->isAlive()) {
            target->takeDamage(damage);
            std::cout << "Dealt " << damage << " damage to player" << std::endl;
        }
    }
}