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
// 7:   Print obstacle positions relative to player

const char debug = 0;

// Target framerate for drawing frames
/**
 * @brief The target framerate for the application.
 *
 * This constant represents the desired framerate for the application. It is used to control the rate at which
 * frames are rendered and updated.
 */
const unsigned int targetFramerate = 60;

// Window settings

/**
 * @brief The default height of the application window.
 *
 * This constant represents the height of the application window in pixels.
 */
const unsigned windowHeight = 512.0f;

/**
 * @brief The default width of the application window.
 *
 * This constant represents the width of the application window in pixels.
 */
const unsigned windowWidth = 1024.f;

/**
 * @brief The maximum speed for the player.
 *
 * This constant represents the maximum speed that the player can gain.
 * It is needed due to limitations of numerical physics calculation methods.
 */
const float playerMaxSpeed = 500.0f;

/**
 * @brief The width of the arrow when drawing out with the mouse.
 *
 * This constant represents the width of the arrow when it is being drawn out with the mouse.
 */
const float arrowWidth = 5.0f;

/**
 * @brief The size of the menu title.
 *
 * This constant represents the size of the menu title text.
 */
const unsigned menuTitleSize = 72;

// Level name max character limit
/**
 * @brief The maximum number of characters allowed for a level name.
 */
const unsigned levelNameCharLimit = 12;