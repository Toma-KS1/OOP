#include "Player.h"

Player::Player(const std::string& name, int health, int score) 
    : GameCharacter(name, health), score(score) {}

Player::~Player() {
}

void Player::addScore(int points) {
    score += points;
}