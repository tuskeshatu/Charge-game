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
    double getRadius() const override { return body.getRadius(); }
    sf::Vector2f getPosition() const override { return body.getPosition(); }
    void setPosition(const sf::RenderWindow &window, sf::Vector2f &newPos) override;
    void draw(sf::RenderWindow &window) const override { window.draw(body); }
};