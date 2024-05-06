#pragma once

// DEBUG LEVELS:
// 0:   None
// 1:   Print fps to cout
// 2:   Print speed and force acting on player
// 3:   Print number of obstacles
// 4:   Print starting speed vector dragged out with mouse

const char debug = 2;

// Target framerate for drawing frames
const char targetFramerate = 60;

// Window height setting
const float windowHeight = 512.0f;
const float windowWidth = 1024.f;

// Max speed for player
const float playerMaxSpeed = 500.0f;

// Arrow width when drawing out with mouse
const float arrowWidth = 5.0f;