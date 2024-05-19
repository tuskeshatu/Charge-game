#include <iostream>
#include <SFML\Graphics.hpp>
#include <cmath>
#include "settings.h"
#include "player.h"

extern const char debug;
extern const float playerMaxSpeed;
extern float deltaTime;

extern sf::RenderWindow window;

// Create body of player
Player::Player(float radius, double charge, double mass, sf::Vector2f pos)
    : Charge(charge), speed(0.0f, 0.0f), mass(mass), body(radius)
{
    setPosition(pos);
    body.setOrigin(radius, radius);
    body.setFillColor(sf::Color::Red);
}

void Player::setPosition(sf::Vector2f &newPos)
{
    if (newPos.x < 0)
        newPos.x = 0;
    else if (newPos.x > window.getSize().x)
        newPos.x = window.getSize().x;
    if (newPos.y < 0)
        newPos.y = 0;
    else if (newPos.y > window.getSize().y)
        newPos.y = window.getSize().y;

    body.setPosition(newPos);
}

// Speed setter
void Player::setSpeed(sf::Vector2f &newSpeed)
{
    speed = newSpeed;
    if (speed.x > playerMaxSpeed)
        speed.x = playerMaxSpeed;
    if (speed.y > playerMaxSpeed)
        speed.y = playerMaxSpeed;
    if (speed.x < -playerMaxSpeed)
        speed.x = -playerMaxSpeed;
    if (speed.y < -playerMaxSpeed)
        speed.y = -playerMaxSpeed;
}

// Updates speed with acceleration and deltaTime
void Player::updateMovement(const sf::Vector2f &acceleration)
{
    sf::Vector2f newSpeed(speed.x + acceleration.x * deltaTime, speed.y += acceleration.y * deltaTime);
    setSpeed(newSpeed);

    if (debug == 2)
        std::cout << "Current speed\t" << std::sqrt(speed.x * speed.x + speed.y * speed.y) << "\tx: "
                  << speed.x << "\ty: " << speed.y << "\t\t";

    sf::Vector2f deltaPos(0.0, 0.0);
    deltaPos.x = speed.x * std::min(deltaTime, 0.0165f);
    deltaPos.y = speed.y * std::min(deltaTime, 0.0165f);

    // Update players position with deltaPos
    body.move(deltaPos);
}