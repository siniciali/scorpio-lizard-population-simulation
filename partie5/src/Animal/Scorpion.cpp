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

void Scorpion::setEatenEnergy()
{
    // Scorpions cannot be eaten, so this is a no-op
}

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

std::string Scorpion::getTextureName() const
{
    return getAppConfig().scorpion_texture;
}

bool Scorpion::eatable(OrganicEntity const* entity) const
{
    return entity->eatableDispatch(this);
}

bool Scorpion::eatableDispatch(const Scorpion* scorpion) const
{
    return false;
}

bool Scorpion::eatableDispatch(const Lizard* lizard) const
{
    return false;
}

bool Scorpion::eatableDispatch(const Cactus* food) const
{
    return false;
}

bool Scorpion::matable(OrganicEntity const* entity) const
{
    return entity->matableDispatch(this);
}

bool Scorpion::matableDispatch(Scorpion const* scorpion) const
{
    // Mating is possible if genders differ and both are eligible
    return ((scorpion->getIfIsFemale() != this->getIfIsFemale())
            and scorpion->getIfCanReproduce()
            and this->getIfCanReproduce());
}

bool Scorpion::matableDispatch(Lizard const* lizard) const
{
    return false;
}

bool Scorpion::matableDispatch(Cactus const* cactus) const
{
    return false;
}

double Scorpion::getEnergyLostFactor() const
{
    return getAppConfig().scorpion_energy_loss_factor;
}

double Scorpion::getInitialEnergy() const
{
    return getAppConfig().scorpion_energy_initial;
}

bool Scorpion::getIfCanReproduce() const
{
    if (getIfIsFemale()) {
        // Female reproduction conditions
        return (!getIfPregnant()
                and getLifetime().asSeconds() >= getAppConfig().scorpion_min_age_mating
                and getEnergyLevel() >= getAppConfig().scorpion_energy_min_mating_female
                and !getIfGestating()
                and !getIfIsDelivering());
    } else {
        // Male reproduction conditions
        return (getLifetime().asSeconds() >= getAppConfig().scorpion_min_age_mating
                and getEnergyLevel() >= getAppConfig().scorpion_energy_min_mating_male);
    }
}

double Scorpion::getGestatingTime() const
{
    return gestating_time;
}

void Scorpion::meet(OrganicEntity* entity)
{
    entity->meetDispatch(this);
}

void Scorpion::meetDispatch(Lizard* lizard)
{
    // No interaction with lizards
}

void Scorpion::meetDispatch(Scorpion* scorpion)
{
    // Attempt mating if both are compatible
    if (scorpion->matable(this) and this->matable(scorpion)) {
        if (getIfIsFemale()) {
            // Female initiates gestation
            setNumberBabies(uniform(getAppConfig().scorpion_min_children, getAppConfig().scorpion_max_children));
            setGestatingCounter(sf::Time::Zero);
            setEnergyLevel(getEnergyLevel() - getNumberBabies() * getAppConfig().scorpion_energy_loss_female_per_child);
        } else {
            // Male loses energy after mating
            setEnergyLevel(getEnergyLevel() - getAppConfig().scorpion_energy_loss_mating_male);
        }
    }
}

void Scorpion::meetDispatch(Cactus* cactus)
{
    // No interaction with cactus
}

void Scorpion::giving_birth()
{
    // Spawn a new scorpion at current position
    getAppEnv().addEntity(new Scorpion(getPosition()));
}

sf::Time Scorpion::getEntityMaxAge() const
{
    return getAppConfig().scorpion_longevity;
}

void Scorpion::incrementCounter() const
{
    getAppEnv().incrementScorpionCounter();
}
