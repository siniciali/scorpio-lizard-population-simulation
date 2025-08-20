#pragma once
#include "Obstacle/Collider.hpp"

class SolidObstacle : public Collider
{

public:
    SolidObstacle(const Vec2d& position, double radius, double orientation);
    virtual ~SolidObstacle() override;
protected:
    double getOrientation() const;
private:
    double orientation;
};
