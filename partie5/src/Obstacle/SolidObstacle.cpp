#include "../Obstacle/SolidObstacle.hpp"

// Constructor initializes base Collider and sets the orientation
SolidObstacle::SolidObstacle(const Vec2d &position, double radius, double orientation) :
    Collider(position, radius),
    orientation(orientation)
{}

SolidObstacle::~SolidObstacle() {}

double SolidObstacle::getOrientation() const
{
    // Return the current orientation of the obstacle
    return orientation;
}

