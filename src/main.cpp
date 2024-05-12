#include <iostream>

#include "game.h"
#include "charge.h"
#include "player.h"
#include "obstacle.h"
#include "settings.h"
#include "level.h"
#include "levelManager.h"

extern const char debug;

int main()
{
    Game game(LevelManager::getInstance()->loadLevel(0));
    game.run();
    return 0;
}