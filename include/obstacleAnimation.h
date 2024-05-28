#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <memory>

#include "animation.h"

class ObstacleAnimation : public Animation
{
public:
    /**
     * @brief Constructs an ObstacleAnimation object with the given filename.
     *
     * @param filename The filename of the texture to load.
     */
    ObstacleAnimation(const Animation::Type type);

    /**
     * @brief Applies a transform to the obstacle animation.
     *
     * @param transform The transform to apply.
     */
    void applyTransform(Charge &toTransform) const override;
};