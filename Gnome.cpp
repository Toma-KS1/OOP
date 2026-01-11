#include "Gnome.h"
#include "Player.h"
#include <iostream>

Gnome::Gnome(const std::string& name) 
    : Enemy(name, 90, 3) {}

Gnome::~Gnome() {
    std::cout << "Gnome " << name << " has been defeated." << std::endl;
}

void Gnome::displayStatus() const {
    std::cout << "Gnome " << name << " | Health: " << health 
              << " | Difficulty: " << difficulty << "/10" << std::endl;
}

void Gnome::specialAbility() {
    if (alive && health > 20) {
        std::cout << name << " plays his trumpet! Other gnomes come to help!" << std::endl;
    } else if (alive) {
        std::cout << name << " is too injured to play the trumpet (needs over 20 health)." << std::endl;
    }
}

void Gnome::attackPlayer(Player* target) {
    if (!alive) {
        std::cout << name << " is dead and cannot attack!" << std::endl;
        return;
    }
    
    if (target && target->isAlive()) {
        std::cout << name << " uses a bow and arrow!" << std::endl;
        int damage = 5 * difficulty;
        
        if (target->isAlive()) {
            target->takeDamage(damage);
            std::cout << "Dealt " << damage << " damage to player" << std::endl;
        }
    }
}