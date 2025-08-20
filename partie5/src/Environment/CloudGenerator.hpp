#pragma once

#include "../Interface/Updatable.hpp"

/**
 * @brief Generates clouds in the environment under specific conditions.
 *
 * The CloudGenerator periodically checks environmental conditions and
 * creates new clouds if criteria such as drought duration and temperature are met.
 */
class CloudGenerator : public Updatable
{
public:
    /**
     * @brief Constructs a CloudGenerator with an initial timer set to zero.
     */
    CloudGenerator();

    /**
     * @brief Destructor for the CloudGenerator.
     */
    ~CloudGenerator() override;

    /**
     * @brief Updates the generator and creates clouds if conditions are accomplished.
     * @param dt Time elapsed since the last update.
     */
    void update(sf::Time dt) override;

private:
    sf::Time tcounter; ///< Time counter used to control cloud generation frequency.
};
