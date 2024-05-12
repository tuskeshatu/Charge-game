#include <SFML\Graphics.hpp>

#include "obstacle.h"
#include "settings.h"

extern const char debug;

Obstacle::Obstacle(const sf::RenderWindow &window, float radius, double charge, sf::Vector2f pos)
    : Charge(charge), body(radius)
{
    setPosition(window, pos);
    body.setOrigin(radius, radius);
    if (charge < 0)
        body.setFillColor(sf::Color::Blue);
    else if (charge > 0)
        body.setFillColor(sf::Color::Green);
    else
        body.setFillColor(sf::Color::White);
}

Obstacle::Obstacle(float radius, double charge, sf::Vector2f pos)
    : Charge(charge), body(radius)
{
    body.setPosition(pos);
    body.setOrigin(radius, radius);
    body.setOrigin(radius, radius);
    if (charge < 0)
        body.setFillColor(sf::Color::Blue);
    else if (charge > 0)
        body.setFillColor(sf::Color::Green);
    else
        body.setFillColor(sf::Color::White);
}

void Obstacle::setPosition(const sf::RenderWindow &window, sf::Vector2f &newPos)
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