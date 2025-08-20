#pragma once
#include "../Animal/Animal.hpp"

#ifndef SCORPION_HPP
#define SCORPION_HPP

#endif // SCORPION_HPP

class Scorpion : public Animal
{

public:

    Scorpion(const Vec2d& initialPosition, double energyLvl, bool isFemale);
    Scorpion(const Vec2d& initialPosition);
    ~Scorpion() override ;

    double getStandardMaxSpeed() const override;
    double getMass() const override;
    double getViewRange() const override;
    double getViewDistance() const override;
    double getRandomWalkRadius() const override;
    double getRandomWalkDistance() const override;
    double getRandomWalkJitter() const override;

    const std::string& getTexture() const override;

    bool eatable(OrganicEntity const* entity) const override;
    bool matable(OrganicEntity const* entity) const override;
    void meet(OrganicEntity* entity) override;


    double getEnergyLossFactor()const override;
    double getInitialEnergy() const override;
    sf::Time getEntityMaxAge() const override;

    void setEatenEnergy() override;

    bool getIfCanReproduce() const override;

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

    double gestating_time;



};
