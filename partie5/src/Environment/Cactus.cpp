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

    // If the soil is humid, the cactus grows
    if (getAppEnv().getHumidity()) {
        if(getEnergyLevel() < getAppConfig().food_max_energy) {
            double new_energy = getEnergyLevel() * getAppConfig().food_growth_rate;
            if (new_energy > getAppConfig().food_max_energy) {
                new_energy=getAppConfig().food_max_energy;
            }
            setEnergyLevel(new_energy);
            setRadius(new_energy);
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
                                 getAppTexture(this->getTextureName())));
    targetWindow.draw(imageToDraw);

    if (isDebugOn()) {
        auto color(sf::Color(20,150,20,30));
        targetWindow.draw(buildCircle(getPosition(), getRadius(), color)); // consequence:
        // a lizard that is
        // further away can
        // access the cacti
    }
}

DrawingPriority Cactus::getDepth() const
{
    return DrawingPriority::CACTUS_PRIORITY;
}

std::string Cactus::getTextureName() const
{
    return getAppConfig().food_texture;
}

bool Cactus::eatable(OrganicEntity const* entity) const
{
    return entity->eatableDispatch(this);
}

// === Double dispatch: edibility logic ===

bool Cactus::eatableDispatch(const Scorpion* scorpion) const
{
    return false;
}
bool Cactus::eatableDispatch(const Lizard* lizard) const
{
    return true;
}

bool Cactus::eatableDispatch(const Cactus* food) const
{
    return false;
}

// === Double dispatch: mating logic ===

bool Cactus::matable(OrganicEntity const* entity) const
{
    return entity->matableDispatch(this);
}

bool Cactus::matableDispatch(Scorpion const* scorpion) const
{
    return false;
}

bool Cactus::matableDispatch(Lizard const* lizard) const
{
    return false;
}

bool Cactus::matableDispatch(Cactus const* cactus) const
{
    return false;
}

bool Cactus::getIfCanReproduce() const
{
    return false;
}

// === Double dispatch: meeting logic ===

void Cactus::meet(OrganicEntity* entity)
{
    return entity->meetDispatch(this);
}

void Cactus::meetDispatch(Lizard* lizard)
{
    // nothing happens
}
void Cactus::meetDispatch(Scorpion* scorpion) {}
void Cactus::meetDispatch(Cactus* cactus) {}


void Cactus::incrementCounter() const
{
    getAppEnv().incrementCactusCounter();
}
