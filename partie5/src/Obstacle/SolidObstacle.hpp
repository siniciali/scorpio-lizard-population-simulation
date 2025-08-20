#pragma once
#include "Obstacle/Collider.hpp"

/**
 * @brief Represents a solid obstacle in the environment.
 *
 * Inherits from Collider and adds an orientation attribute,
 * which can be used to define the facing direction of the obstacle.
 */
class SolidObstacle : public Collider
{

public:
    /**
     * @brief Constructs a SolidObstacle with a given position, radius, and orientation.
     *
     * @param position The center position of the obstacle in the toric world.
     * @param radius The radius of the obstacle.
     * @param orientation The orientation angle (in radians or degrees, depending on usage).
     */
    SolidObstacle(const Vec2d& position, double radius, double orientation);

    /**
     * @brief Virtual destructor for SolidObstacle.
     */
    virtual ~SolidObstacle();

protected:
    /**
     * @brief Gets the orientation of the obstacle.
     * @return The orientation angle of the obstacle.
     */
    double getOrientation() const;

private:
    const double orientation;
};
