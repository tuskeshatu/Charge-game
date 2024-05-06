#include <iostream>
#include <SFML\Graphics.hpp>
#include <cmath>
#include "settings.h"
#include "player.h"

extern const char debug;

// Create body of player
Player::Player(float radius, double charge, double mass, sf::Vector2i pos)
    : Charge(charge, radius, pos, sf::Color::Red), speed(0.0f, 0.0f), mass(mass)
{
}

// Mass getter
double Player::getMass() const
{
    return mass;
}

void Player::setSpeed(const sf::Vector2f &speed)
{
    this->speed = speed;
}

// Updates speed with acceleration and deltaTime
void Player::updateMovement(const sf::Vector2f &acceleration, double deltaTime)
{
    speed.x += acceleration.x * deltaTime;
    speed.y += acceleration.y * deltaTime;

    if (debug == 2)
        std::cout << "Current speed\t" << std::sqrt(speed.x * speed.x + speed.y * speed.y) << "\t";
    

    sf::Vector2f deltaPos(0.0, 0.0);
    deltaPos.x = speed.x * deltaTime;
    deltaPos.y = speed.y * deltaTime;

    // Update players position with deltaPos
    movePlayer(deltaPos);
}