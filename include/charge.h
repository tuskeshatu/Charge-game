#pragma once
#include <SFML\Graphics.hpp>

class Charge
{
private:
    // Quantity of electric charge of a charge
    double electricCharge;
    
public:
    Charge(const double charge);
    virtual void setPosition(sf::Vector2f& newPos) = 0;
    virtual const sf::CircleShape &getBody() const = 0;
    double getElectricCharge() const { return electricCharge; }
};