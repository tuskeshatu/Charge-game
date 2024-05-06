#include "game.h"
#include "charge.h"
#include "player.h"
#include "obstacle.h"
#include "settings.h"

extern const char debug;

#define DEBUG true

int main()
{
    Game game;
    game.run();
    return 0;
}