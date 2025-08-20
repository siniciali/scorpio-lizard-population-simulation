#pragma once
#include "../Obstacle/Collider.hpp"
#include "../Utility/Vec2d.hpp"

class Scorpion;
class Lizard;
class Cactus;

class OrganicEntity : public Collider
{

public:
    OrganicEntity (const Vec2d& position, double size, double energyLvl);
    virtual ~OrganicEntity() override; // on met le virtual car OrganicEntity est une classe abstraite
    virtual const std::string& getTexture() const = 0;
    void update(sf::Time age) override;

    virtual bool eatable (const OrganicEntity* other) const = 0;
    virtual bool eatableBy(const Scorpion* scorpion) const = 0;
    virtual bool eatableBy(const Lizard* lizard) const = 0;
    virtual bool eatableBy(const Cactus* food) const = 0;

    // on ajoute dans organic entity plutot que dans animal en envisageant le cas où les cactus pourraient devenir capables de se
    // reproduire et qu'on voulait implémenter cette extension plus tard...

    virtual bool matable(OrganicEntity const* other) const = 0;
    virtual bool canMate(Scorpion const* scorpion) const = 0;
    virtual bool canMate(Lizard const* lizard) const = 0;
    virtual bool canMate(Cactus const* food) const = 0;
    virtual bool getIfCanReproduce() const = 0;

    virtual void meet(OrganicEntity* entity) = 0;
    virtual void meetWith(Lizard* lizard) = 0;
    virtual void meetWith(Scorpion* scorpion) = 0;
    virtual void meetWith(Cactus* cactus) = 0;

    double getEnergyLevel() const;
    void setEnergyLevel(const double newenergy);
    sf::Time getLifetime() const;
    double getEntityMinEnergy() const;
    void updateLifetime(sf::Time dt);
    bool isTooWeak() const;
    bool isTooOld() const;
    bool isDead() const;

    virtual sf::Time getEntityMaxAge() const;

    virtual void setEatenEnergy() = 0;

private:

    double energyLevel;
    sf::Time lifetime;

};

