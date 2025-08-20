#include "../Environment/Cactus.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "../Environment/Environment.hpp"

Cactus::Cactus(const Vec2d& position)
    : OrganicEntity(position, getAppConfig().food_energy, getAppConfig().food_energy)
{}

Cactus::~Cactus() { }

void Cactus::update(sf::Time dt)
{

    OrganicEntity::update(dt);

    if (getAppEnv().getHumidity()) {

        if(getEnergyLevel() < getAppConfig().food_max_energy) {

            double current_energy = getEnergyLevel() * getAppConfig().food_growth_rate;

            if (current_energy > getAppConfig().food_max_energy) {
                current_energy=getAppConfig().food_max_energy;
            }

            setEnergyLevel(current_energy);

        }

    }

}

void Cactus::setEatenEnergy()
{
    setEnergyLevel(getEnergyLevel() - getAppConfig().animal_meal_retention);
}

void Cactus::draw(sf::RenderTarget& targetWindow) const
{
    auto imageToDraw(buildSprite(this->getPosition(),
                                 (getEnergyLevel()),
                                 getAppTexture(this->getTexture())));
    targetWindow.draw(imageToDraw);
    if (isDebugOn()) {
        auto color(sf::Color(20,150,20,30));
        targetWindow.draw(buildCircle(getPosition(), getRadius(), color));
    }
}

DrawingPriority Cactus::getDepth() const
{
    return DrawingPriority::CACTUS_PRIORITY;
}

const std::string& Cactus::getTexture() const
{
    return getAppConfig().food_texture;
}

bool Cactus::eatable(OrganicEntity const* entity) const
{
    return entity->eatableBy(this);
}

bool Cactus::eatableBy(const Scorpion* scorpion) const
{
    return false;
}
bool Cactus::eatableBy(const Lizard* lizard) const
{
    return true;
}

bool Cactus::eatableBy(const Cactus* food) const
{
    return false;
}

bool Cactus::matable(OrganicEntity const* entity) const
{
    return entity->canMate(this);
}

bool Cactus::canMate(Scorpion const* scorpion) const
{
    return false;
}

bool Cactus::canMate(Lizard const* lizard) const
{
    return false;
}

bool Cactus::canMate(Cactus const* cactus) const
{
    return false;
}

void Cactus::meet(OrganicEntity* entity)
{
    return entity->meetWith(this);
}

void Cactus::meetWith(Lizard* lizard)
{

}

void Cactus::meetWith(Scorpion* scorpion) {}
void Cactus::meetWith(Cactus* cactus) {}



bool Cactus::getIfCanReproduce() const
{
    return false;
}
