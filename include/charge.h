#pragma once
#include <SFML\Graphics.hpp>

class Charge
{
private:
    // Quantity of electric charge of a charge
    double electricCharge;
    // TODO: not only circle charges!
    
public:
    Charge(const double charge);
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void setPosition(const sf::Vector2f&) = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual double getRadius() const = 0;
    double getElectricCharge() const { return electricCharge; }
};