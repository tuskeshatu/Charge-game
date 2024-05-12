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
    Player(const sf::RenderWindow& window, float radius = 100.0f, double charge = 10.0, double mass = 1.0, sf::Vector2f pos = sf::Vector2f(250.0, 250.0));
    double getMass() const { return mass; }
    double getRadius() const override { return body.getRadius(); }
    sf::Vector2f getPosition() const override { return body.getPosition(); }
    sf::Vector2f getSpeed() const { return speed; }
    void setPosition(const sf::RenderWindow& window, sf::Vector2f& newPos) override;
    void setSpeed(sf::Vector2f& newSpeed);
    void updateMovement(const sf::Vector2f& accelaration, const double deltaTime);
    void draw(sf::RenderWindow& window)const override { window.draw(body); }
};