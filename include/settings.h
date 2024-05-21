#pragma once
#include <chrono>

// DEBUG LEVELS:
// 0:   None
// 1:   Print fps to cout
// 2:   Print speed and force acting on player
// 3:   Print number of obstacles
// 4:   Print starting speed vector dragged out with mouse
// 5:   Debug LevelManager: level loading/saving
// 6:   Display menu items

const char debug = 1;

// Target framerate for drawing frames
const unsigned int targetFramerate = 60;

// Window height setting
const unsigned windowHeight = 512.0f;
const unsigned windowWidth = 1024.f;

// Max speed for player
const float playerMaxSpeed = 500.0f;

// Arrow width when drawing out with mouse
const float arrowWidth = 5.0f;

// Character sizes for texts
const unsigned menuTitleSize = 72;