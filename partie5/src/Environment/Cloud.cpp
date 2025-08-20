#include "../Environment/Cloud.hpp"
#include "../Application.hpp"
#include "../Environment/Environment.hpp"
#include "../Utility/Utility.hpp"

Cloud::Cloud(const Vec2d& position, double radius)
    : Collider(position, radius),
      isEvaporated(radius < getAppConfig().cloud_evaporation_size) // Initial evaporation check
{}

void Cloud::draw(sf::RenderTarget& targetWindow) const
{
    if (!isEvaporated) {
        // Draw the cloud sprite if it hasn't evaporated
        auto imageToDraw = buildSprite(
                               getPosition(),
                               getRadius(),
                               getAppTexture(getAppConfig().cloud_texture)
                           );
        targetWindow.draw(imageToDraw);
    }
}

Cloud::~Cloud() {}

void Cloud::update(sf::Time dt)
{
    if (isEvaporated) return;

    // Check if temperature exceeds evaporation threshold
    if (getAppEnv().getTemperature() > getAppConfig().cloud_evaporation_temperature) {
        // Reduce radius based on evaporation rate
        setRadius(getRadius()- getAppConfig().cloud_evaporation_rate * getRadius()) ;

        // Mark as evaporated if below minimum size
        if (getRadius() < getAppConfig().cloud_evaporation_size) {
            isEvaporated = true;
        }
    }
}

bool Cloud::getEvaporationState() const
{
    return isEvaporated;
}
