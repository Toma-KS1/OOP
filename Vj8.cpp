#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "GameCharacter.h"
#include "Player.h"
#include "Enemy.h"
#include "Warrior.h"
#include "Mage.h"
#include "Gnome.h"
#include "Boss.h"

int main() {
    std::cout << "=== GAME CHARACTER BATTLE SIMULATION ===\n" << std::endl;
    
    std::vector<std::unique_ptr<GameCharacter>> characters;
    
    characters.push_back(std::unique_ptr<GameCharacter>(new Warrior("Conan")));
    characters.push_back(std::unique_ptr<GameCharacter>(new Mage("Merlin")));
    characters.push_back(std::unique_ptr<GameCharacter>(new Gnome("Gnomeo")));
    characters.push_back(std::unique_ptr<GameCharacter>(new Gnome("Sneaky")));
    characters.push_back(std::unique_ptr<GameCharacter>(new Boss("Dragon")));
    
    std::cout << "=== INITIAL STATUS ===" << std::endl;
    for (const auto& character : characters) {
        character->displayStatus();
    }
    std::cout << std::endl;
    
    Warrior* conan = dynamic_cast<Warrior*>(characters[0].get());
    Mage* merlin = dynamic_cast<Mage*>(characters[1].get());
    Gnome* gnomeo = dynamic_cast<Gnome*>(characters[2].get());
    Gnome* sneaky = dynamic_cast<Gnome*>(characters[3].get());
    Boss* dragon = dynamic_cast<Boss*>(characters[4].get());
    
    std::cout << "=== BATTLE BEGINS ===\n" << std::endl;
    
    std::cout << "1. Conan attacks Gnomeo:" << std::endl;
    if (conan && gnomeo && conan->isAlive() && gnomeo->isAlive()) {
        conan->attackEnemy(gnomeo);
        std::cout << "Status after attack:" << std::endl;
        conan->displayStatus();
        gnomeo->displayStatus();
    }
    std::cout << std::endl;
    
    std::cout << "2. Merlin attacks Sneaky:" << std::endl;
    if (merlin && sneaky && merlin->isAlive() && sneaky->isAlive()) {
        merlin->attackEnemy(sneaky);
        std::cout << "Status after attack:" << std::endl;
        merlin->displayStatus();
        sneaky->displayStatus();
    }
    std::cout << std::endl;
    
    std::cout << "3. Gnomeo attacks Conan:" << std::endl;
    if (gnomeo && conan && gnomeo->isAlive() && conan->isAlive()) {
        gnomeo->attackPlayer(conan);
        std::cout << "Status after attack:" << std::endl;
        gnomeo->displayStatus();
        conan->displayStatus();
    }
    std::cout << std::endl;
    
    std::cout << "4. Merlin attacks Gnomeo:" << std::endl;
    if (merlin && gnomeo && merlin->isAlive() && gnomeo->isAlive()) {
        merlin->attackEnemy(gnomeo);
        std::cout << "Status after attack:" << std::endl;
        merlin->displayStatus();
        gnomeo->displayStatus();
    }
    std::cout << std::endl;
    
    std::cout << "5. Dragon attacks Merlin:" << std::endl;
    if (dragon && merlin && dragon->isAlive() && merlin->isAlive()) {
        dragon->attackPlayer(merlin);
        std::cout << "Status after attack:" << std::endl;
        dragon->displayStatus();
        merlin->displayStatus();
    }
    std::cout << std::endl;
    
    std::cout << "6. Merlin attacks Gnomeo:" << std::endl;
    if (merlin && gnomeo && merlin->isAlive() && gnomeo->isAlive()) {
        merlin->attackEnemy(gnomeo);
        std::cout << "Status after attack:" << std::endl;
        merlin->displayStatus();
        gnomeo->displayStatus();
    }
    std::cout << std::endl;
    
    std::cout << "7. Conan attacks Dragon:" << std::endl;
    if (conan && dragon && conan->isAlive() && dragon->isAlive()) {
        conan->attackEnemy(dragon);
        std::cout << "Status after attack:" << std::endl;
        conan->displayStatus();
        dragon->displayStatus();
    }
    std::cout << std::endl;
    
    std::cout << "8. Merlin attacks Dragon:" << std::endl;
    if (merlin && dragon && merlin->isAlive() && dragon->isAlive()) {
        merlin->attackEnemy(dragon);
        std::cout << "Status after attack:" << std::endl;
        merlin->displayStatus();
        dragon->displayStatus();
    }
    std::cout << std::endl;
    
    std::cout << "=== SPECIAL ABILITIES ===" << std::endl;
    for (const auto& character : characters) {
        if (character->isAlive()) {
            character->specialAbility();
            character->displayStatus();
        }
    }
    std::cout << std::endl;
    
std::cout << "=== FINAL STATUS ===" << std::endl;

std::vector<GameCharacter*> aliveCharacters;
GameCharacter* highestHealthChar = nullptr;
int maxHealth = -1;

for (const auto& character : characters) {
    if (character->isAlive()) {
        character->displayStatus();
        aliveCharacters.push_back(character.get());
        if (character->getHealth() > maxHealth) {
            maxHealth = character->getHealth();
            highestHealthChar = character.get();
        }
    } else {
        std::cout << character->getName() << " is dead." << std::endl;
    }
}

std::cout << std::endl;

std::cout << "=== BATTLE SUMMARY ===" << std::endl;
if (!merlin->isAlive()) {
    std::cout << "Merlin is dead as expected." << std::endl;
} else {
    std::cout << "ERROR: Merlin should be dead but is alive!" << std::endl;
}

std::cout << "Number of survivors: " << aliveCharacters.size() << std::endl;

if (highestHealthChar) {
    std::cout << "Character with most health: " << highestHealthChar->getName() 
              << " with " << maxHealth << " health." << std::endl;
    
    if (highestHealthChar == dragon) {
        std::cout << "Boss (Dragon) has the most health as expected." << std::endl;
    } else {
        std::cout << "ERROR: Boss should have the most health!" << std::endl;
    }
}
}