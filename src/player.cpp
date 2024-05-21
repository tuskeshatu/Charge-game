#include <iostream>
#include <SFML\Graphics.hpp>
#include <cmath>
#include "settings.h"
#include "player.h"

extern const char debug;
extern const float playerMaxSpeed;
extern float deltaTime;

extern sf::RenderWindow window;

// Create body of player and set physical traits
Player::Player(float radius, double charge, double mass, sf::Vector2f pos)
    : Charge(charge), speed(0.0f, 0.0f), mass(mass), body(std::make_shared<sf::CircleShape>(radius))
{
    // Set position with setter to get protection for out of bounds type of stuff
    body->setOrigin(radius, radius);
    setPosition(pos);
    // Color of player is red for now
    body->setFillColor(sf::Color::Red);
}

// Set position, guard against placing outside of window
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

    body->setPosition(newPos);
}

// Set speed, don't let speed go above maximum speed for stability of simulation
void Player::setSpeed(const sf::Vector2f &newSpeed)
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
    // Limit maximum deltaTime to prevent bugs relating to too long deltaTime.
    // For example if simulation stops because of resize or window dragging events,
    // the simulation clock doesn't stop.
    deltaTime = std::min(deltaTime, 0.0165f);
    if (debug == 1)
        std::cout << "dT:\t" << deltaTime << std::endl;

    // Calculate new speed by adding change of speed to last speed
    // (basically integrating the acceleration as a function of time)
    sf::Vector2f newSpeed(speed.x + acceleration.x * deltaTime, speed.y += acceleration.y * deltaTime);
    setSpeed(newSpeed);

    if (debug == 2)
        std::cout << "Current speed\t" << std::sqrt(speed.x * speed.x + speed.y * speed.y) << "\tx: "
                  << speed.x << "\ty: " << speed.y << "\t\t";

    // Calculate deltaPos the same way speed is calculated
    sf::Vector2f deltaPos(0.0, 0.0);
    deltaPos.x = speed.x * deltaTime;
    deltaPos.y = speed.y * deltaTime;

    // Update players position with deltaPos
    body->move(deltaPos);
}