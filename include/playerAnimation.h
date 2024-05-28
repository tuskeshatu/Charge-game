#pragma once

#include <SFML\Graphics.hpp>

#include "animation.h"

class PlayerAnimation : public Animation
{
public:
    /**
     * @brief Constructs a PlayerAnimation object with the given filename.
     *
     * @param filename The filename of the texture to load.
     */
    PlayerAnimation();

    /**
     * @brief Applies a transform to the player animation.
     *
     * @param transform The transform to apply.
     */
    void applyTransform(Charge &toTransform) const override;
};