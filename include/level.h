#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include <string>
#include <memory>

#include "obstacle.h"
#include "settings.h"

extern const unsigned windowWidth;
extern const unsigned windoHeight;

/**
 * @class Level
 * @brief Represents a game level.
 */
class Level
{
private:
    std::string name; /**< The name of the level. */
    sf::Vector2u size; /**< The size of the level. */
    std::vector<std::shared_ptr<Obstacle>> obstacles; /**< The obstacles in the level. */
    sf::Vector2f playerStartPos; /**< The starting position of the player in the level. */

public:
    /**
     * @brief Constructs a Level object.
     * @param levelName The name of the level.
     * @param levelSize The size of the level.
     * @param obstacles The obstacles in the level.
     * @param playerStartPos The starting position of the player in the level.
     */
    Level(const std::string &levelName = "empty_level", const sf::Vector2u &levelSize = sf::Vector2u(windowWidth, windowHeight), const std::vector<std::shared_ptr<Obstacle>> &obstacles = std::vector<std::shared_ptr<Obstacle>>(), const sf::Vector2f &playerStartPos = sf::Vector2f(windowWidth / 2, windowHeight / 2));

    /**
     * @brief Adds an obstacle to the level.
     * @param newObstacle The obstacle to add.
     */
    void addObstacle(const std::shared_ptr<Obstacle> &newObstacle);

    /**
     * @brief Gets the obstacles in the level.
     * @return The obstacles in the level.
     */
    const std::vector<std::shared_ptr<Obstacle>> &getObstacles() const { return obstacles; }

    /**
     * @brief Gets the starting position of the player in the level.
     * @return The starting position of the player.
     */
    const sf::Vector2f &getPlayerStartPos() const { return playerStartPos; }

    /**
     * @brief Gets the name of the level.
     * @return The name of the level.
     */
    const std::string &getName() const { return name; }

    /**
     * @brief Gets the size of the level.
     * @return The size of the level.
     */
    const sf::Vector2u &getSize() const { return size; }

    /**
     * @brief Sets the name of the level.
     * @param newName The new name of the level.
     * @return True if the name was successfully set, false otherwise.
     */
    const bool setName(const std::string& newName);

    /**
     * @brief Sets the starting position of the player in the level.
     * @param newPos The new starting position of the player.
     */
    void setPlayerStartPos(const sf::Vector2f &newPos) { playerStartPos = newPos; }

    /**
     * @brief Sets the size of the level.
     * @param newSize The new size of the level.
     */
    void setSize(const sf::Vector2u &newSize) { size = newSize; }

    /**
     * @brief Clears all obstacles from the level.
     */
    void clearObstacles() { obstacles.clear(); }

    /**
     * @brief Removes an obstacle from the level.
     * @param idx The index of the obstacle to remove.
     */
    void removeObstacle(size_t idx) { obstacles.erase(obstacles.begin() + idx); }
};