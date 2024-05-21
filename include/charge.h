#pragma once
#include <SFML\Graphics.hpp>
#include <memory>

/**
 * @class Charge
 * @brief Represents an electric charge.
 * 
 * The Charge class provides a way to represent an electric charge. It contains
 * information about the quantity of electric charge and provides methods to
 * access and manipulate this information.
 */
class Charge
{
private:
    double electricCharge; /**< Quantity of electric charge of a charge */
    
public:
    /**
     * @brief Constructs a Charge object with the given electric charge.
     * 
     * @param charge The quantity of electric charge.
     */
    Charge(const double charge);
    
    /**
     * @brief Sets the position of the charge.
     * 
     * This method is pure virtual and must be implemented by derived classes.
     * It sets the position of the charge to the given new position.
     * 
     * @param newPos The new position of the charge.
     */
    virtual void setPosition(sf::Vector2f& newPos) = 0;
    
    /**
     * @brief Gets the body of the charge.
     * 
     * This method is pure virtual and must be implemented by derived classes.
     * It returns a constant reference to the body of the charge.
     * 
     * @return The body of the charge.
     */
    virtual const std::shared_ptr<sf::CircleShape> &getBody() const = 0;
    
    /**
     * @brief Gets the electric charge of the charge.
     * 
     * This method returns the quantity of electric charge of the charge.
     * 
     * @return The electric charge of the charge.
     */
    double getElectricCharge() const { return electricCharge; }
};