#pragma once
#include <SFML\Graphics.hpp>

#include "charge.h"

class Obstacle : public Charge
{
private:
    sf::CircleShape body;

public:
    Obstacle(float radius = 100.0f, double charge = 10.0, sf::Vector2f pos = sf::Vector2f(250.0, 250.0), sf::Color color = sf::Color::Blue);
    double getRadius() const override { return body.getRadius(); }
    sf::Vector2f getPosition() const override { return body.getPosition(); }
    void setPosition(const sf::Vector2f& newPos) override { body.setPosition(newPos); }
    void draw(sf::RenderWindow& window) const override { window.draw(body); }
};