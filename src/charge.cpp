#include <SFML\Graphics.hpp>

#include "charge.h"

Charge::Charge(double charge, float radius, sf::Vector2i pos, sf::Color color)
    : electricCharge(charge), body(radius)
{
    body.setFillColor(color);
    body.setOrigin(body.getRadius(), body.getRadius());
    body.setPosition(float(pos.x), float(pos.y));
}

void Charge::draw(sf::RenderWindow &window)
{
    window.draw(body);
}

void Charge::setPosition(const sf::Vector2f& pos)
{
    body.setPosition(pos);
}

sf::Vector2f Charge::getPosition() const
{
    return body.getPosition();
}

double Charge::getElectricCharge() const
{
    return electricCharge;
}

void Charge::movePlayer(const sf::Vector2f& deltaPos)
{
    body.move(deltaPos);
}