#include "Lizard.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "../Random/Random.hpp"

Lizard::Lizard(const Vec2d& initialPosition, double energyLvl, bool isFemale)
    : Animal(initialPosition, getAppConfig().lizard_size, energyLvl, isFemale),
      gestating_time(getAppConfig().lizard_gestation_time)
{}

Lizard::Lizard(const Vec2d& initialPosition)
    : Animal(initialPosition, getAppConfig().lizard_size, getAppConfig().lizard_energy_initial, uniform(0, 1) == 0),
      gestating_time(getAppConfig().lizard_gestation_time)
{}

Lizard::~Lizard() {}

double Lizard::getStandardMaxSpeed() const
{
    return getAppConfig().lizard_max_speed;
}

double Lizard::getMass() const
{
    return getAppConfig().lizard_mass;
}

double Lizard::getViewRange() const
{
    return getAppConfig().lizard_view_range;
}

double Lizard::getViewDistance() const
{
    return getAppConfig().lizard_view_distance;
}

double Lizard::getRandomWalkRadius() const
{
    return getAppConfig().lizard_random_walk_radius;
}

double Lizard::getRandomWalkDistance() const
{
    return getAppConfig().lizard_random_walk_distance;
}

double Lizard::getRandomWalkJitter() const
{
    return getAppConfig().lizard_random_walk_jitter;
}

void Lizard::update(sf::Time dt)
{
    // Randomly flip texture orientation with 10% probability
    if (bernoulli(0.1)) {
        texture_orientation = !texture_orientation;
    }

    Animal::update(dt);
}

std::string Lizard::getTextureName() const
{
    if (getIfIsFemale()) {
        if (texture_orientation) {
            return getAppConfig().lizard_texture_female_down;
        } else {
            return getAppConfig().lizard_texture_female;
        }
    } else {
        if (texture_orientation) {
            return getAppConfig().lizard_texture_male_down;
        } else {
            return getAppConfig().lizard_texture_male;
        }
    }
}

void Lizard::setEatenEnergy()
{
    setEnergyLevel(0.0);
}

bool Lizard::eatable(OrganicEntity const* entity) const
{
    return entity->eatableDispatch(this);
}

bool Lizard::eatableDispatch(const Scorpion* scorpion) const
{
    return true;
}

bool Lizard::eatableDispatch(const Lizard* lizard) const
{
    return false;
}

bool Lizard::eatableDispatch(const Cactus* food) const
{
    return false;
}

bool Lizard::matable(OrganicEntity const* entity) const
{
    return entity->matableDispatch(this);
}

bool Lizard::matableDispatch(Scorpion const* scorpion) const
{
    return false;
}

bool Lizard::matableDispatch(Lizard const* lizard) const
{
    return ((lizard->getIfIsFemale() != this->getIfIsFemale())
            and lizard->getIfCanReproduce()
            and this->getIfCanReproduce());
}

bool Lizard::matableDispatch(Cactus const* cactus) const
{
    return false;
}

double Lizard::getEnergyLostFactor()const
{
    return getAppConfig().lizard_energy_loss_factor;
}

double Lizard::getInitialEnergy() const
{
    return getAppConfig().lizard_energy_initial;
}

bool Lizard::getIfCanReproduce() const
{
    if(getIfIsFemale()) {
        return (!getIfPregnant()
                and (getLifetime()).asSeconds()>=getAppConfig().lizard_min_age_mating
                and getEnergyLevel()>=getAppConfig().lizard_energy_min_mating_female
                and !getIfGestating()
                and !getIfIsDelivering()); // multiple animals can't reproduce at the same time
    } else {
        return ((getLifetime()).asSeconds()>=getAppConfig().lizard_min_age_mating
                and getEnergyLevel()>=getAppConfig().lizard_energy_min_mating_male);
    }
}

double Lizard::getGestatingTime() const
{
    return gestating_time;
}

void Lizard::meet(OrganicEntity* entity)
{
    entity->meetDispatch(this);
}

void Lizard::meetDispatch(Lizard* lizard)
{
    if(lizard->matable(this) and this->matable(lizard)) {
        if(getIfIsFemale()) {
            // Female becomes pregnant and loses energy based on number of babies
            setNumberBabies(uniform(getAppConfig().lizard_min_children, getAppConfig().lizard_max_children));
            setGestatingCounter(sf::Time::Zero);
            setEnergyLevel(getEnergyLevel() - getNumberBabies() * getAppConfig().lizard_energy_loss_female_per_child);

            // Female turns toward male to initiate mating
            setDirection(lizard->getPosition() - this->getPosition());
        } else {
            // Male loses energy and turns toward female
            setEnergyLevel(getEnergyLevel() - getAppConfig().lizard_energy_loss_mating_male);
            setDirection(lizard->getPosition() - this->getPosition());
        }
    }
}

void Lizard::meetDispatch(Scorpion* scorpion) {}
void Lizard::meetDispatch(Cactus* cactus) {}

void Lizard::giving_birth()
{
    getAppEnv().addEntity(new Lizard(getPosition()));
}

sf::Time Lizard::getEntityMaxAge() const
{
    return getAppConfig().lizard_longevity;
}

void Lizard::incrementCounter() const
{
    getAppEnv().incrementLizardCounter();
}
