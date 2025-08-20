#pragma once

#include "../Animal/Animal.hpp"

#include "../Utility/Vec2d.hpp"

#ifndef LIZARD_HPP
#define LIZARD_HPP

#endif // LIZARD_HPP

class Lizard : public Animal
{
public:

    Lizard(const Vec2d& initialPosition, double energyLvl, bool isFemale);
    Lizard(const Vec2d& initialPosition);
    ~Lizard() override;

    double getStandardMaxSpeed() const override;
    double getMass() const override;
    double getViewRange() const override;
    double getViewDistance() const override;
    double getRandomWalkRadius() const override;
    double getRandomWalkDistance() const override;
    double getRandomWalkJitter() const override;

    const std::string& getTexture() const override;
    bool isDown();

    bool eatable(OrganicEntity const* entity) const override;
    bool matable(OrganicEntity const* entity) const override;
    void meet(OrganicEntity* entity) override;



    sf::Time getEntityMaxAge() const override;
    double getEnergyLossFactor()const override;
    double getInitialEnergy() const override;

    void update(sf::Time dt) override;

    void setEatenEnergy() override;

    double getGestatingTime() const override;

    void giving_birth() override;

private:

    bool eatableBy(const Scorpion* scorpion) const override;
    bool eatableBy(const Lizard* lizard) const override;
    bool eatableBy(const Cactus* food) const override;

    bool canMate(Scorpion const* scorpion) const override;
    bool canMate(Lizard const* lizard) const override;
    bool canMate(Cactus const* food) const override;

    void meetWith(Lizard* lizard) override;
    void meetWith(Scorpion* scorpion) override;
    void meetWith(Cactus* cactus) override;

    bool getIfCanReproduce() const override;

    bool texture_orientation=false;

    double gestating_time;

};
