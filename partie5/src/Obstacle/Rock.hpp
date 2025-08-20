#pragma once
#include "../Obstacle/SolidObstacle.hpp"
#include "../Utility/Vec2d.hpp"

/**
 * @brief Represents a static rock obstacle in the simulation.
 *
 * A Rock is a non-moving, drawable object with a randomized radius and orientation.
 * It inherits from SolidObstacle and overrides draw and update methods.
 */
class Rock : public SolidObstacle
{
public:
    /**
     * @brief Constructs a Rock at a given position with random radius and orientation.
     *
     * @param position The center position of the rock in the toric world.
     */
    Rock(const Vec2d& position);

    /**
     * @brief Virtual destructor for Rock.
     */
    ~Rock() override;

    /**
     * @brief Displays the rock on the simulation screen.
     *
     * Draws the rock using its texture and orientation. If debug mode is enabled,
     * also draws a translucent circle representing its collision boundary.
     *
     * @param targetWindow The window where the rock will be rendered.
     */
    void draw(sf::RenderTarget& targetWindow) const override final;

    /**
     * @brief Updates the rock's state.
     *
     * Rocks are static and do not change over time, so this method is intentionally empty.
     *
     * @param dt Time step for the update (unused).
     */
    void update(sf::Time dt) override final;
};
