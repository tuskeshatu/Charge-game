#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include "levelManager.h"
#include "nlohmann\json.hpp"
#include "obstacle.h"
#include "settings.h"

extern const char debug;

// Get instance of singleton LevelManager
LevelManager *LevelManager::getInstance()
{
    static LevelManager instance;
    return &instance;
}

// Constructor
LevelManager::LevelManager()
{
    // See if levels.txt (index of loadable levels) exists
    std::ifstream loadablesFile;
    loadablesFile.open("levels/index.txt");
    if (!loadablesFile)
    {
        if (debug == 5)
            std::cout << "Couldn't locate index.txt..." << std::endl;
        // Check if the "levels" directory exists
        if (!std::filesystem::exists("levels"))
        {
            // Create the "levels" directory
            std::filesystem::create_directory("levels");
            if (debug == 5)
                std::cout << "Created \"levels\" directory" << std::endl;
        }

        // Check if the "index.txt" file exists inside the "levels" directory
        std::ifstream indexFile("levels/index.txt");
        if (!indexFile)
        {
            // Create the "index.txt" file inside the "levels" directory
            std::ofstream newIndexFile("levels/index.txt");
            if (!newIndexFile)
            {
                if (debug == 5)
                    std::cout << "Couldn't create 'index.txt' file" << std::endl;
                return;
            }
            // Close index file
            newIndexFile.close();
            if (debug == 5)
                std::cout << "Created 'index.txt' file" << std::endl;
        }
        indexFile.close();
        return;
    }
    // If yes load loadables
    std::string levelName;
    while (loadablesFile >> levelName)
    {
        loadables.push_back(levelName);
    }
    if (debug == 5)
        std::cout << "Loaded index.txt..." << std::endl;
    loadablesFile.close();
}

// Destructor updates index when destroying LevelManager
LevelManager::~LevelManager()
{
    updateIndex();
}

// Update index file based on loadables
void LevelManager::updateIndex() const
{
    // Open levels.txt for writing
    std::ofstream loadablesFile;
    loadablesFile.open("levels/index.txt");
    if (!loadablesFile)
    {
        if (debug == 5)
            std::cout << "Couldn't open index.txt for writing" << std::endl;
        return;
    }

    // Write loadables to the file, separated by newline
    for (const std::string &levelName : loadables)
    {
        loadablesFile << levelName << "\n";
        if (debug == 5)
            std::cout << "Loaded " + levelName + " to index.txt..." << std::endl;
    }
    loadablesFile.close();
    if (debug == 5)
        std::cout << "Finished saving index.txt" << std::endl;
}

// Loads a level by name
Level LevelManager::loadLevel(const std::string &levelName) const
{
    // Look for level to be loaded in loadables
    if (std::find(loadables.begin(), loadables.end(), levelName) != loadables.end())
    {
        // Try to open the json file
        std::ifstream levelFile("./levels/" + levelName + ".json");
        if (!levelFile)
            throw std::runtime_error("LevelManager: Level load error: " + levelName + ".json");

        // Deserialize it
        nlohmann::json jsonData;
        levelFile >> jsonData;

        // Read name, size, playerStartPos and fill obstacles
        std::string name = jsonData["name"];
        sf::Vector2u size(jsonData["size"]["x"], jsonData["size"]["y"]);
        
        // Create obstacles to be filled
        std::vector<std::shared_ptr<Obstacle>> obstacles;

        // Auto because type names are confusing with this library
        // Load fields of each obstacle into obstacle object
        for (const auto &obstacleData : jsonData["obstacles"])
        {
            // Load fields
            double charge = obstacleData["charge"];
            sf::Vector2f position(obstacleData["position"]["x"], obstacleData["position"]["y"]);
            double radius = obstacleData["radius"];
            
            // Construct obstacle object
            Obstacle obstacle(radius, charge, position);
            // Make shared pointer and push to obstacles
            obstacles.push_back(std::make_shared<Obstacle>(obstacle));
        }

        // Load playerstartpos
        sf::Vector2f playerStartPos(jsonData["playerStartPos"]["x"], jsonData["playerStartPos"]["y"]);
        // Construct level and return it
        return Level(levelName, size, obstacles, playerStartPos);
    }
    // If error occured throw runtime error
    else
    {
        throw std::runtime_error("LevelManager: Level not found: " + levelName + ".json");
    }
    if (debug == 5)
        std::cout << "Loaded level: " + levelName << std::endl;
}

// Load level by index
Level LevelManager::loadLevel(const size_t &levelIndex) const
{
    // Create level to be returned
    Level retLevel;
    // Catch errors occurring from overindexing, non-existent files etc...
    // Return empty level if error occured
    try
    {
        retLevel = loadLevel(loadables.at(levelIndex));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return Level();
    }
    return retLevel;
}

// This function saves the given level object to a JSON file.
void LevelManager::saveLevel(const Level &level)
{
    // Open the file for writing
    std::ofstream levelFile("./levels/" + level.getName() + ".json");
    if (!levelFile)
        throw std::runtime_error("LevelManager: Level save error: " + level.getName() + ".json");

    // Write level data to json object
    nlohmann::json jsonData;
    jsonData["name"] = level.getName();
    jsonData["size"]["x"] = level.getSize().x;
    jsonData["size"]["y"] = level.getSize().y;
    jsonData["playerStartPos"]["x"] = level.getPlayerStartPos().x;
    jsonData["playerStartPos"]["y"] = level.getPlayerStartPos().y;

    // Create json objects for every obstacle
    for (const auto &obstacle : level.getObstacles())
    {
        nlohmann::json obstacleData;
        obstacleData["charge"] = obstacle.get()->getElectricCharge();
        obstacleData["position"]["x"] = obstacle.get()->getBody()->getPosition().x;
        obstacleData["position"]["y"] = obstacle.get()->getBody()->getPosition().y;
        obstacleData["radius"] = obstacle.get()->getBody()->getRadius();

        jsonData["obstacles"].push_back(obstacleData);
    }

    // Write to file
    levelFile << jsonData;

    // Add level name to loadables if it is not already present
    if (std::find(loadables.begin(), loadables.end(), level.getName()) == loadables.end())
        loadables.push_back(level.getName());

    if (debug == 5)
        std::cout << "Saved level: " + level.getName() << std::endl;

    levelFile.close();
}

// Delete a level by providing level name
const bool LevelManager::deleteLevel(const std::string &levelName)
{
    // Look for levelName in loadables with iterator
    // Auto because of complicated type name of iterators
    auto it = std::find(loadables.begin(), loadables.end(), levelName);

    // If end was reached without finding the level return false
    if (it == loadables.end())
    {
        return false;
    }

    // Remove levelName from loadables
    loadables.erase(it);

    // Delete the corresponding JSON file
    std::string filePath = "./levels/" + levelName + ".json";
    if (std::remove(filePath.c_str()) != 0) {
        throw std::runtime_error("LevelManager: Failed to delete level file: " + levelName + ".json");
    }

    return true;
}