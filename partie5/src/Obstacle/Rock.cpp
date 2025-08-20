#include "../Obstacle/Rock.hpp"
#include "../Random/Random.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

Rock::Rock(const Vec2d &position) :
    SolidObstacle (position,
                   uniform(getAppConfig().simulation_world_size/50,
                           2*getAppConfig().simulation_world_size/50),
                   uniform(-PI, PI))
{}

Rock::~Rock() {}

void Rock::draw (sf::RenderTarget &targetWindow) const
{

    if (isDebugOn()) {
        auto color(sf::Color(20,150,20,30));
        targetWindow.draw(buildCircle(getPosition(), getRadius(), color));
    }

    auto imageToDraw(buildSprite(getPosition(),
                                 getRadius()*2,
                                 getAppTexture(getAppConfig().rock_texture),
                                 getOrientation()/DEG_TO_RAD));

    targetWindow.draw(imageToDraw);
}

void Rock::update(sf::Time dt)
{
    // rocks do not change over time but update must be defined otherwise Rock
    // would remain an abstract class
}





