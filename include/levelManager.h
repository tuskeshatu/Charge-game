#include <string>
#include <vector>

#include <level.h>

// Singleton LevelManager class to avoid discrepencies between loadables of multiple instances

/**
 * @class LevelManager
 * @brief Manages the levels in the game.
 *
 * The LevelManager class is responsible for managing the levels in the game. It provides
 * functionality to load, save, delete, and retrieve information about the levels.
 */
class LevelManager
{
private:
    std::vector<std::string> loadables; /**< A vector of strings representing the loadable levels. */

    LevelManager(); /**< Private constructor to enforce singleton pattern. */
    ~LevelManager(); /**< Destructor. */

public:
    /**
     * @brief Get the instance of the LevelManager.
     * @return A pointer to the LevelManager instance.
     */
    static LevelManager *getInstance();

    /**
     * @brief Get the list of loadable levels.
     * @return A constant reference to the vector of loadable levels.
     */
    const std::vector<std::string>& getLoadables() const { return loadables; }

    /**
     * @brief Update the index of the levels.
     *
     * This function updates the index of the levels based on the current state of the game.
     */
    void updateIndex() const;

    /**
     * @brief Load a level by its name.
     * @param levelName The name of the level to load.
     * @return The loaded Level object.
     */
    Level loadLevel(const std::string &levelName) const;

    /**
     * @brief Load a level by its index.
     * @param levelIndex The index of the level to load. 0 is always the oldest created level.
     * @return The loaded Level object.
     */
    Level loadLevel(const size_t &levelIndex) const;

    /**
     * @brief Load a default level.
     * @return The loaded default Level object.
     */
    Level loadLevel() const { return Level(); }

    /**
     * @brief Save a level.
     * @param level The Level object to save.
     */
    void saveLevel(const Level &level);

    /**
     * @brief Delete a level by its name.
     * @param levelName The name of the level to delete.
     * @return True if the level was successfully deleted, false otherwise.
     */
    const bool deleteLevel(const std::string &levelName);
};