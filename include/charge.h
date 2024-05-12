#pragma once
#include <SFML\Graphics.hpp>

class Charge
{
private:
    // Quantity of electric charge of a charge
    double electricCharge;
    
public:
    Charge(const double charge);
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void setPosition(const sf::RenderWindow& window, sf::Vector2f& newPos) = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual double getRadius() const = 0;
    double getElectricCharge() const { return electricCharge; }
};