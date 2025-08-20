#pragma once

#ifndef CLOUD_HPP
#define CLOUD_HPP

#include "../Obstacle/Collider.hpp"
#include "../Utility/Utility.hpp"



class Cloud : public Collider
{
public:

    Cloud(const Vec2d& position, double radius);

    ~Cloud() override;

    void draw(sf::RenderTarget& targetWindow) const override;

    void update(sf::Time dt) override;

    bool getEvaporationState() const;

private:
    double radius;
    bool isEvaporated;
};

#endif // CLOUD_HPP
