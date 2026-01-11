#include "Mage.h"
#include "Enemy.h"
#include <iostream>

Mage::Mage(const std::string& name) 
    : Player(name, 80, 0), mana(100) {}

Mage::~Mage() {
    std::cout << "Mage " << name << " has vanished." << std::endl;
}

void Mage::displayStatus() const {
    std::cout << "Mage " << name << " | Health: " << health 
              << " | Score: " << score << " | Mana: " << mana << std::endl;
}

void Mage::specialAbility() {
    if (alive && health > 50) {
        std::cout << name << " teleports away from danger!" << std::endl;
    } else if (alive) {
        std::cout << name << " is too injured to teleport (needs over 50 health)." << std::endl;
    }
}

void Mage::attackEnemy(Enemy* target) {
    if (!alive) {
        std::cout << name << " is dead and cannot attack!" << std::endl;
        return;
    }
    
    if (target && target->isAlive()) {
        if (mana >= 20) {
            std::cout << name << " throws a fireball!" << std::endl;
            int damage = 40;
            mana -= 20;
            
            if (target->isAlive()) {
                target->takeDamage(damage);
                std::cout << "Dealt " << damage << " damage to enemy" 
                          << " | Mana left: " << mana << std::endl;
                
                if (!target->isAlive()) {
                    std::cout << "Enemy has been defeated!" << std::endl;
                    addScore(10);
                }
            }
        } else {
            std::cout << name << " attacks with a stick!" << std::endl;
            int damage = 20;
            
            if (target->isAlive()) {
                target->takeDamage(damage);
                std::cout << "Dealt " << damage << " damage to enemy" 
                          << " | Mana: " << mana << std::endl;
                
                if (!target->isAlive()) {
                    std::cout << "Enemy has been defeated!" << std::endl;
                    addScore(10);
                }
            }
        }
    }
}