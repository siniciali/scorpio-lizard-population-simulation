#pragma once

#ifndef CACTUS_HPP
#define CACTUS_HPP

#include "../Environment/OrganicEntity.hpp"
#include "../Utility/Vec2d.hpp"
#include "../Environment/OrganicEntity.hpp"


class Cactus : public OrganicEntity
{
public:

    Cactus(const Vec2d& position);
    ~Cactus() override;

    void update(sf::Time dt) override;
    void draw(sf::RenderTarget& targetWindow) const override;
    const std::string& getTexture() const override;
    DrawingPriority getDepth() const override;
    bool eatable(OrganicEntity const* entity) const override;
    bool matable(OrganicEntity const* other) const override;
    void meet(OrganicEntity* other) override;

    void setEatenEnergy() override;



private:

    bool eatableBy(const Scorpion* scorpion) const override;
    bool eatableBy(const Lizard* lizard) const override;
    bool eatableBy(const Cactus* food) const override;

    bool canMate(Scorpion const* scorpion) const override;
    bool canMate(Lizard const* lizard) const override;
    bool canMate(Cactus const* food) const override;
    bool getIfCanReproduce() const override;


    void meetWith(Lizard* lizard) override;
    void meetWith(Scorpion* scorpion) override;
    void meetWith(Cactus* cactus) override;


};

#endif // CACTUS_HPP
