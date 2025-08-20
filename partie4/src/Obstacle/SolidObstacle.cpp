#include "Obstacle/SolidObstacle.hpp"

SolidObstacle::SolidObstacle(const Vec2d &position, double radius, double orientation) :
    Collider (position, radius),
    orientation(orientation)
{}

SolidObstacle::~SolidObstacle() {}

double SolidObstacle::getOrientation() const
{
    return orientation;
}

