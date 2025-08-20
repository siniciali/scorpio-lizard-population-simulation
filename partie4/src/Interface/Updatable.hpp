/*
 * POOSV 2025
 */

#pragma once

#include <SFML/System.hpp>

/*!
 * @class Updatable
 *
 * @brief Represents an entity that evolves over time
 */
class Updatable
{
public:
    virtual ~Updatable() { /* Default virtual dtor */ }

    virtual void update(sf::Time dt) = 0;
};


