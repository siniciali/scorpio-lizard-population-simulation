#include "../Animal/Scorpion.hpp"
#include "../Application.hpp"
#include "../Random/Random.hpp"

Scorpion::Scorpion(const Vec2d& initialPosition, double energyLvl, bool isFemale)
    : Animal(initialPosition, getAppConfig().scorpion_size, energyLvl, isFemale),
      gestating_time(getAppConfig().scorpion_gestation_time)
{}

Scorpion::Scorpion(const Vec2d& initialPosition)
    : Animal(initialPosition, getAppConfig().scorpion_size, getAppConfig().scorpion_energy_initial, uniform(0, 1) == 0),
      gestating_time(getAppConfig().scorpion_gestation_time)
{}

Scorpion::~Scorpion() {}

double Scorpion::getStandardMaxSpeed() const
{
    return getAppConfig().scorpion_max_speed;
}

void Scorpion::setEatenEnergy() {} //a scorpio cannot be eaten

double Scorpion::getMass() const
{
    return getAppConfig().scorpion_mass;
}

double Scorpion::getViewRange() const
{
    return getAppConfig().scorpion_view_range;
}

double Scorpion::getViewDistance() const
{
    return getAppConfig().scorpion_view_distance;
}

double Scorpion::getRandomWalkRadius() const
{
    return getAppConfig().scorpion_random_walk_radius;
}

double Scorpion::getRandomWalkDistance() const
{
    return getAppConfig().scorpion_random_walk_distance;
}

double Scorpion::getRandomWalkJitter() const
{
    return getAppConfig().scorpion_random_walk_jitter;
}

const std::string& Scorpion::getTexture() const
{
    return getAppConfig().scorpion_texture;
}

bool Scorpion::eatable(OrganicEntity const* entity) const
{
    return entity->eatableBy(this);
}

bool Scorpion::eatableBy(const Scorpion* scorpion) const
{
    return false;
}
bool Scorpion::eatableBy(const Lizard* lizard) const
{
    return false;
}

bool Scorpion::eatableBy(const Cactus* food) const
{
    return false;
}

bool Scorpion::matable(OrganicEntity const* entity) const
{



    return entity->canMate(this);
}

bool Scorpion::canMate(Scorpion const* scorpion) const
{
    return ((scorpion->getIfIsFemale() != this->getIfIsFemale())
            and scorpion->getIfCanReproduce()
            and this->getIfCanReproduce());
}

bool Scorpion::canMate(Lizard const* lizard) const
{
    return false;
}

bool Scorpion::canMate(Cactus const* cactus) const
{
    return false;
}

double Scorpion::getEnergyLossFactor()const
{
    return getAppConfig().scorpion_energy_loss_factor;
}

double Scorpion::getInitialEnergy() const
{
    return getAppConfig().scorpion_energy_initial;
}

bool Scorpion::getIfCanReproduce() const
{

    if(getIfIsFemale()) {

        return (!getIfPregnant()
                and (getLifetime()).asSeconds()>=getAppConfig().scorpion_min_age_mating
                and getEnergyLevel()>=getAppConfig().scorpion_energy_min_mating_female
                and !getIfGestating()
                and !getIfIsDelivering());

    }

    else {

        return ((getLifetime()).asSeconds()>=getAppConfig().scorpion_min_age_mating
                and getEnergyLevel()>=getAppConfig().scorpion_energy_min_mating_male);

    }

}

double Scorpion::getGestatingTime() const
{
    return gestating_time;
}

void Scorpion::meet(OrganicEntity* entity)
{
    entity->meetWith(this);
}

void Scorpion::meetWith(Lizard* lizard) {}

void Scorpion::meetWith(Scorpion* scorpion)
{
    if(scorpion->matable(this) and this->matable(scorpion)) {
        if(getIfIsFemale()) {
            setNumberBabies(uniform(getAppConfig().scorpion_min_children, getAppConfig().scorpion_max_children));
            setGestatingCounter(sf::Time::Zero);
            setEnergyLevel(getEnergyLevel()-getNumberBabies()*getAppConfig().scorpion_energy_loss_female_per_child);
        } else {
            setEnergyLevel(getEnergyLevel()-getAppConfig().scorpion_energy_loss_mating_male);
        }
    }
}
void Scorpion::meetWith(Cactus* cactus) {}

void Scorpion::giving_birth()
{

    getAppEnv().addEntity(new Scorpion(getPosition()));

}

sf::Time Scorpion::getEntityMaxAge() const
{
    return getAppConfig().scorpion_longevity;
}
