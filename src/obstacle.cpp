#include <SFML\Graphics.hpp>

#include "obstacle.h"
#include "settings.h"

extern const char debug;

Obstacle::Obstacle(float radius, double charge, sf::Vector2i pos, sf::Color color)
: Charge(charge, radius, pos, color)
{
}