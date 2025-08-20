#pragma once

#include "../Animal/Lizard.hpp"



class WaveLizard : public Lizard
{
public:

    WaveLizard(const Vec2d& initialPosition, double energyLvl, bool isFemale);
    WaveLizard(const Vec2d& initialPosition);
    ~WaveLizard() override;

    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& targetWindow) const override;

private:

    sf::Time wave_counter;
};
