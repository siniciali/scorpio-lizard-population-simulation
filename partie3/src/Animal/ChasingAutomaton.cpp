#include "../Animal/ChasingAutomaton.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "../Utility/Vec2d.hpp"
#include "../algorithm"
#include "../Utility/constants.hpp"


ChasingAutomaton::ChasingAutomaton(const Vec2d& position)
    :   Collider(position, ANIMAL_RADIUS),
        speed (0.0),
        targetPosition (0, 0),
        direction (1, 0)
{}

double ChasingAutomaton::getStandardMaxSpeed()const
{
    return ANIMAL_MAX_SPEED;
}

double ChasingAutomaton::getMass()const
{
    return  ANIMAL_MASS;
}

void ChasingAutomaton::setTargetPosition (const Vec2d& newPosition)
{
    targetPosition = newPosition;
}

Vec2d ChasingAutomaton::getSpeedVector () const
{
    Vec2d res(direction.x()*speed,direction.y()*speed);
    return res;
}

void ChasingAutomaton::draw(sf::RenderTarget& targetWindow)const
{
    sf::Texture& texture = getAppTexture(GHOST_TEXTURE);
    auto image_to_draw(buildSprite(this->getPosition(),
                                   (this->getRadius()*2),
                                   texture));
    targetWindow.draw(image_to_draw);
    targetWindow.draw(buildCircle(targetPosition, 5.0, sf::Color(255, 0, 0)));
}

void ChasingAutomaton::setDecelerationMode(DecelerationMode mode)
{
    currentDeceleration = mode;
}

double ChasingAutomaton::getDeceleration(const DecelerationMode& mode) const
{

    if (mode==Weak) {
        return 0.3;
    } else if (mode==Strong) {
        return 0.9;
    }

    else {
        return 0.6;
    }

}



Vec2d ChasingAutomaton::getAttractionForce() const
{

    Vec2d res;

    Vec2d vectToTarget=targetPosition-this->getPosition();

    if (vectToTarget.length() == 0) {
        return Vec2d(0, 0);
    }

    double wantedSpeed = std::min((vectToTarget.length()/getDeceleration(currentDeceleration)), getStandardMaxSpeed());

    Vec2d vTarget(vectToTarget*wantedSpeed/vectToTarget.length());

    res=vTarget-getSpeedVector();

    return res;
}

void ChasingAutomaton::update(sf::Time dt)
{

    //application de l'algorythme d'Euler-Cromer

    double elapsedTime = dt.asSeconds();

    Vec2d acceleration = getAttractionForce() / getMass();

    Vec2d newSpeed = getSpeedVector() + acceleration * elapsedTime;

    if (newSpeed.length() > getStandardMaxSpeed()) {
        newSpeed = newSpeed.normalised() * getStandardMaxSpeed();
    }

    direction = newSpeed.normalised();

    speed=newSpeed.length();

    this->move(newSpeed*elapsedTime);

}





