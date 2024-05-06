#include <SFML\Graphics.hpp>

#include "obstacle.h"
#include "settings.h"

extern const char debug;

Obstacle::Obstacle(float radius, double charge, sf::Vector2f pos, sf::Color color)
: Charge(charge), body(radius)
{
    body.setPosition(pos);
    body.setOrigin(radius, radius);
    body.setFillColor(color);
}