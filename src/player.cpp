#include <iostream>
#include <SFML\Graphics.hpp>
#include <cmath>
#include "settings.h"
#include "player.h"

extern const char debug;
extern const float playerMaxSpeed;

// Create body of player
Player::Player(const sf::RenderWindow& window, float radius, double charge, double mass, sf::Vector2f pos)
    : Charge(charge), speed(0.0f, 0.0f), mass(mass), body(radius)
{
    setPosition(window, pos);
    body.setOrigin(radius, radius);
    body.setFillColor(sf::Color::Red);
}

void Player::setPosition(const sf::RenderWindow &window, sf::Vector2f &newPos)
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
void Player::updateMovement(const sf::Vector2f &acceleration, double deltaTime)
{
    sf::Vector2f newSpeed(speed.x + acceleration.x * deltaTime, speed.y += acceleration.y * deltaTime);
    setSpeed(newSpeed);

    if (debug == 2)
        std::cout << "Current speed\t" << std::sqrt(speed.x * speed.x + speed.y * speed.y) << "\tx: "
                  << speed.x << "\ty: " << speed.y << "\t\t";

    sf::Vector2f deltaPos(0.0, 0.0);
    deltaPos.x = speed.x * deltaTime;
    deltaPos.y = speed.y * deltaTime;

    // Update players position with deltaPos
    body.move(deltaPos);
}