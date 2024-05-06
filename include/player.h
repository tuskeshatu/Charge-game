#pragma once
#include <SFML\Graphics.hpp>

#include "charge.h"

class Player : public Charge
{
private:
    sf::Vector2f speed;
    double mass;
public:
    Player(float radius = 100.0f, double charge = 10.0, double mass = 1.0, sf::Vector2i pos = sf::Vector2i(250.0, 250.0));
    double getMass() const;
    void setSpeed(const sf::Vector2f& speed);
    void updateMovement(const sf::Vector2f& accelaration, const double deltaTime);
};