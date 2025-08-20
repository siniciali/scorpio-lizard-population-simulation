/*
 * POOSV 2025
 * Marco Antognini & Jamila Sam
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <Interface/DrawingPriority.hpp>

/*!
 * @class Drawable
 *
 * @brief Represents an entity that can be represented graphically
 */
class Drawable
{
public:
    virtual ~Drawable() = default;
    virtual void draw(sf::RenderTarget& target) const = 0;
    virtual DrawingPriority getDepth() const
    {
        return DrawingPriority::DEFAULT_PRIORITY;
    }
};
