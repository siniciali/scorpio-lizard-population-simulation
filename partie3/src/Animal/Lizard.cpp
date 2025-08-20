#include "../Animal/Lizard.hpp"
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

    // on fait changer la texture dans environ 10% des intervalles de temps
    if (bernoulli(0.1)) {
        texture_orientation = !texture_orientation;
    }

    Animal::update(dt);

}

const std::string& Lizard::getTexture() const
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
    return entity->eatableBy(this);
}

bool Lizard::eatableBy(const Scorpion* scorpion) const
{
    return true;
}
bool Lizard::eatableBy(const Lizard* lizard) const
{
    return false;
}

bool Lizard::eatableBy(const Cactus* food) const
{
    return false;
}

bool Lizard::matable(OrganicEntity const* entity) const
{
    return entity->canMate(this);
}

bool Lizard::canMate(Scorpion const* scorpion) const
{
    return false;
}

bool Lizard::canMate(Lizard const* lizard) const
{
    return ((lizard->getIfIsFemale() != this->getIfIsFemale())
            and lizard->getIfCanReproduce()
            and this->getIfCanReproduce());
}

bool Lizard::canMate(Cactus const* cactus) const
{
    return false;
}


double Lizard::getEnergyLossFactor()const
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
                and !getIfIsDelivering());

    }

    else {

        return ((getLifetime()).asSeconds()>=getAppConfig().lizard_min_age_mating
                and getEnergyLevel()>=getAppConfig().lizard_energy_min_mating_male);

    }

    return false;

}

double Lizard::getGestatingTime() const
{
    return gestating_time;
}

void Lizard::meet(OrganicEntity* entity)
{

    entity->meetWith(this);


}

void Lizard::meetWith(Lizard* lizard)
{
    if(lizard->matable(this) and this->matable(lizard)) {
        if(getIfIsFemale()) {
            // setPregnancy(true);
            setNumberBabies(uniform(getAppConfig().lizard_min_children, getAppConfig().lizard_max_children));
            setGestatingCounter(sf::Time::Zero);
            setEnergyLevel(getEnergyLevel()-getNumberBabies()*getAppConfig().lizard_energy_loss_female_per_child);

            setDirection(lizard->getPosition() - this->getPosition()); // si un mâle entre en collision avec une femelle
            // mais que la femelle ne le voit pas la femelle se retourne pour que l'acouplement puisse commencer
        } else {
            setEnergyLevel(getEnergyLevel()-getAppConfig().lizard_energy_loss_mating_male);
            setDirection(lizard->getPosition() - this->getPosition()); // si une femelle entre en collision avec un male
            // mais que le male ne le voit pas le male se retourne pour que l'acouplement puisse commencer
        }
    }
}

void Lizard::meetWith(Scorpion* scorpion) {}
void Lizard::meetWith(Cactus* cactus) {}

void Lizard::giving_birth()
{

    getAppEnv().addEntity(new Lizard(getPosition()));

}

sf::Time Lizard::getEntityMaxAge() const
{
    return getAppConfig().lizard_longevity;
}

