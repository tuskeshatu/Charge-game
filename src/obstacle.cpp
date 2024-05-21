#include <SFML\Graphics.hpp>
#include <memory>

#include "obstacle.h"
#include "settings.h"

extern const char debug;
extern sf::RenderWindow window;

// Constructor
Obstacle::Obstacle(const float radius, const double charge, const sf::Vector2f &pos)
    : Charge(charge), body(std::make_shared<sf::CircleShape>(radius))
{
    // Set origin and position
    body->setOrigin(radius, radius);
    body->setPosition(pos);

    // Set color based on charge (+ or -)
    if (charge < 0)
        body->setFillColor(sf::Color::Blue);
    else if (charge > 0)
        body->setFillColor(sf::Color::Green);
    else
        body->setFillColor(sf::Color::White);
}

// Set position, guard against placing outside of window
void Obstacle::setPosition(sf::Vector2f &newPos)
{
    // Clip coordinates to extremeties of the window
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