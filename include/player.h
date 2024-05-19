#pragma once
#include <SFML\Graphics.hpp>

#include "charge.h"

class Player : public Charge
{
private:
    sf::Vector2f speed;
    const double mass;
    sf::CircleShape body;

public:
    Player(float radius = 7.0f, double charge = 1.0, double mass = 15.0, sf::Vector2f pos = sf::Vector2f(250.0, 250.0));
    double getMass() const { return mass; }
    sf::Vector2f getSpeed() const { return speed; }
    const sf::CircleShape &getBody() const override { return body; }
    void setPosition(sf::Vector2f &newPos) override;
    void setSpeed(sf::Vector2f &newSpeed);
    void updateMovement(const sf::Vector2f &accelaration);
};