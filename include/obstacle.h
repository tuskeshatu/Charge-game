#pragma once
#include <SFML\Graphics.hpp>

#include "charge.h"

class Obstacle : public Charge
{
private:
public:
    Obstacle(float radius = 100.0f, double charge = 10.0, sf::Vector2i pos = sf::Vector2i(250.0, 250.0), sf::Color color = sf::Color::Blue);
};