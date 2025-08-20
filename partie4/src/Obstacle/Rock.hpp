#pragma once
#include "Obstacle/SolidObstacle.hpp"


class Rock : public SolidObstacle
{
public:
    Rock (const Vec2d& position);
    ~Rock () override;

    void draw(sf::RenderTarget &targetWindow) const override;
    void update(sf::Time dt) override;

};
