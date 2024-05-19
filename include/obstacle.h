#pragma once
#include <SFML\Graphics.hpp>

#include "charge.h"

class Obstacle : public Charge
{
private:
    sf::CircleShape body;

public:
    Obstacle(const sf::RenderWindow &window, float radius = 100.0f, double charge = 10.0, sf::Vector2f pos = sf::Vector2f(250.0, 250.0));
    Obstacle(float radius = 100.0f, double charge = 10.0, sf::Vector2f pos = sf::Vector2f(250.0, 250.0));
    const sf::CircleShape &getBody() const override {return body;}
    void setPosition(sf::Vector2f &newPos) override;
};