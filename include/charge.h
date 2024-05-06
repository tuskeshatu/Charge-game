#pragma once
#include <SFML\Graphics.hpp>

class Charge
{
private:
    // Quantity of electric charge of a charge
    double electricCharge;
    // Body of charge
    // TODO: not only circle charges!
    sf::CircleShape body;
public:
    Charge(double charge, float radius, sf::Vector2i po, sf::Color color);
    void draw(sf::RenderWindow& window);
    void setPosition(const sf::Vector2f&);
    sf::Vector2f getPosition() const;
    double getElectricCharge() const;
    void movePlayer(const sf::Vector2f& deltaPos);
};