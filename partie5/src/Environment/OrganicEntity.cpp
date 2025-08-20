#include "../Environment/OrganicEntity.hpp"
#include "../Application.hpp"

OrganicEntity::OrganicEntity(const Vec2d& positionCenter, double size, double energyLvl)
    : Collider(positionCenter, size / 2.0), energyLevel(energyLvl), lifetime(sf::Time::Zero)
{}

OrganicEntity::~OrganicEntity() {}

void OrganicEntity::update(sf::Time dt)
{
    // Update the entity's age
    updateLifetime(dt);
}

double OrganicEntity::getEnergyLevel() const
{
    return energyLevel;
}

void OrganicEntity::setEnergyLevel(const double& newenergy)
{
    energyLevel = newenergy;
}

void OrganicEntity::updateLifetime(sf::Time dt)
{
    lifetime += dt;
}

bool OrganicEntity::isTooWeak() const
{
    // Check if energy is below survival threshold
    return (energyLevel < getEntityMinEnergy());
}

bool OrganicEntity::isTooOld() const
{
    return (getLifetime() > this->getEntityMaxAge());
}

bool OrganicEntity::isDead() const
{
    return (isTooWeak() or isTooOld());
}

sf::Time OrganicEntity::getLifetime() const
{
    return lifetime;
}

double OrganicEntity::getEntityMinEnergy() const
{
    // get minimum energy for a generic spieces
    return getAppConfig().animal_min_energy;
}

sf::Time OrganicEntity::getEntityMaxAge() const
{
    // Default max age (can be overridden)
    return sf::seconds(1E9);
}
