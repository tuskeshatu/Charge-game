#pragma once
#include <vector>
#include <SFML\Graphics.hpp>
#include <string>
#include <memory>

#include "obstacle.h"
#include "settings.h"

extern const unsigned windowWidth;
extern const unsigned windoHeight;

class Level
{
private:
    std::string name;
    sf::Vector2u size;
    std::vector<std::shared_ptr<Obstacle>> obstacles;
    sf::Vector2f playerStartPos;

public:
    Level(const std::string &levelName = "empty_level", const sf::Vector2u &levelSize = sf::Vector2u(windowWidth, windowHeight), const std::vector<std::shared_ptr<Obstacle>> &obstacles = std::vector<std::shared_ptr<Obstacle>>(), const sf::Vector2f &playerStartPos = sf::Vector2f(windowWidth / 2, windowHeight / 2));
    ~Level() {}
    // Add object to game instance
    void addObstacle(const Obstacle newObstacle);
    // Getters mostly for jsonification
    const std::vector<std::shared_ptr<Obstacle>> &getObstacles() const { return obstacles; }
    const sf::Vector2f &getPlayerStartPos() const { return playerStartPos; }
    const std::string getName() const { return name; }
    const sf::Vector2u getSize() const { return size; }
    void setPlayerStartPos(const sf::Vector2f &newPos) { playerStartPos = newPos; }
    void setSize(const sf::Vector2u &newSize) { size = newSize; }
    void clearObstacles() { obstacles.clear(); }
};