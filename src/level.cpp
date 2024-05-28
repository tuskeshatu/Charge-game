#include <vector>
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>

#include "obstacle.h"
#include "player.h"
#include "level.h"
#include "settings.h"

extern const char debug;
extern const unsigned levelNameCharLimit;

Level::Level(const std::string &levelName, const sf::Vector2u &levelSize, const std::vector<std::shared_ptr<Obstacle>> &obstacles, const sf::Vector2f &playerStartPos)
    : name(levelName), size(levelSize), obstacles(obstacles), playerStartPos(playerStartPos)
{
}


// Sets name of level. Max character limit defined in settings.h
const bool Level::setName(const std::string& newName)
{
    // New name can't be too long or empty or "Empty Level"
    if (newName.length() > levelNameCharLimit || newName.empty() || newName == "Empty Level" || newName == "empty level" || newName == "Empty level" || newName == "empty Level")
        return false;

    name = newName;
    return true;
}

// Add obstacle to level
void Level::addObstacle(const std::shared_ptr<Obstacle> &newObstacle)
{
    // Obstacles stored as shared pointers, because of rendering as drawable*
    obstacles.push_back(newObstacle);
    if (debug == 3)
        std::cout << "obstacle count:\t" << obstacles.size() << std::endl;
}