#include <string>
#include <vector>

#include <level.h>

// Singleton LevelManager class to avoid discrepencies between loadables
// of multiple instances
class LevelManager
{
private:
    std::vector<std::string> loadables;
    static LevelManager *instance;

    LevelManager();
    ~LevelManager();

public:
    static LevelManager *getInstance();

    void updateIndex() const;
    Level loadLevel(const std::string &levelName) const;
    Level loadLevel(const size_t &levelIndex) const;
    void saveLevel(const Level &level);
};