#include "GameCharacter.h"
#include <iostream>

GameCharacter::GameCharacter(const std::string& name, int health) 
    : name(name), health(health), alive(true) {}

GameCharacter::~GameCharacter() {
}

void GameCharacter::takeDamage(int damage) {
    if (alive && damage > 0) {
        health -= damage;
        if (health <= 0) {
            health = 0;
            alive = false;
        }
    }
}