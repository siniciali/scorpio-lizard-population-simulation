#include "../Environment/Cloud.hpp"
#include "../Application.hpp"
#include "../Environment/Environment.hpp"

Cloud::Cloud(const Vec2d& position, double radius)
    : Collider(position, radius), radius(radius), isEvaporated(radius < getAppConfig().cloud_evaporation_size)
{}

void Cloud::draw(sf::RenderTarget& targetWindow) const
{

    if (!isEvaporated) {

        auto imageToDraw(buildSprite(getPosition(),
                                     radius,
                                     getAppTexture(getAppConfig().cloud_texture)));
        targetWindow.draw(imageToDraw);

    }

}

Cloud::~Cloud()
{

}

void Cloud::update(sf::Time dt )
{

    if (isEvaporated) {
        return;
    }

    if (getAppEnv().getTemperature() > getAppConfig().cloud_evaporation_temperature) {

        radius -= getAppConfig().cloud_evaporation_rate * radius;

        if (radius < getAppConfig().cloud_evaporation_size) {

            isEvaporated=true;

        }

    }


}

bool Cloud::getEvaporationState() const
{
    return isEvaporated;
}
