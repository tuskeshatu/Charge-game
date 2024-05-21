#pragma once
#include <SFML\Graphics.hpp>
#include <memory>

#include "charge.h"

/**
 * @class Player
 * @brief Represents a player in the game.
 * 
 * The Player class inherits from the Charge class and represents a player in the game.
 * It contains information about the player's speed, mass, and body shape.
 */
class Player : public Charge
{
private:
    sf::Vector2f speed; /**< The speed of the player. */
    const double mass; /**< The mass of the player. */
    std::shared_ptr<sf::CircleShape> body; /**< The body shape of the player. */

public:
    /**
     * @brief Constructs a new Player object.
     * 
     * @param radius The radius of the player's body shape.
     * @param charge The charge of the player.
     * @param mass The mass of the player.
     * @param pos The initial position of the player.
     */
    Player(float radius = 7.0f, double charge = 1.0, double mass = 15.0, sf::Vector2f pos = sf::Vector2f(250.0, 250.0));

    /**
     * @brief Gets the mass of the player.
     * 
     * @return The mass of the player.
     */
    const double getMass() const { return mass; }

    /**
     * @brief Gets the speed of the player.
     * 
     * @return The speed of the player. Returns as value to enable calculations for other functions.
     */
    sf::Vector2f getSpeed() const { return speed; }

    /**
     * @brief Gets the body shape of the player.
     * 
     * @return The body shape of the player.
     */
    const std::shared_ptr<sf::CircleShape> &getBody() const override { return body; }

    /**
     * @brief Sets the position of the player.
     * 
     * @param newPos The new position of the player.
     */
    void setPosition(sf::Vector2f &newPos) override;

    /**
     * @brief Sets the speed of the player.
     * 
     * @param newSpeed The new speed of the player.
     */
    void setSpeed(const sf::Vector2f &newSpeed);

    /**
     * @brief Updates the movement of the player based on the given acceleration.
     * 
     * @param acceleration The acceleration to apply to the player's movement.
     */
    void updateMovement(const sf::Vector2f &acceleration);
};