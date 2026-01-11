#include "Warrior.h"
#include "Enemy.h"
#include <iostream>

Warrior::Warrior(const std::string& name) 
    : Player(name, 120, 0), shieldActive(false) {}

Warrior::~Warrior() {
    std::cout << "Warrior " << name << " has fallen." << std::endl;
}

void Warrior::displayStatus() const {
    std::cout << "Warrior " << name << " | Health: " << health 
              << " | Score: " << score 
              << " | Shield: " << (shieldActive ? "Active" : "Inactive") << std::endl;
}

void Warrior::specialAbility() {
    if (alive) {
        std::cout << name << " activates shield! Next attack damage reduced by 50%." << std::endl;
        shieldActive = true;
    }
}

void Warrior::attackEnemy(Enemy* target) {
    if (!alive) {
        std::cout << name << " is dead and cannot attack!" << std::endl;
        return;
    }
    
    if (target && target->isAlive()) {
        std::cout << name << " attacks with a sword!" << std::endl;
        int damage = 20;
        
        if (target->isAlive()) {
            target->takeDamage(damage);
            std::cout << "Dealt " << damage << " damage to enemy" << std::endl;
            
            if (!target->isAlive()) {
                std::cout << "Enemy has been defeated!" << std::endl;
                addScore(10);
            }
        }
    }
}