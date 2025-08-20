#include "Animal/Animal.hpp"
#include "Application.hpp"
#include "../Utility/Utility.hpp"
#include <Utility/Vec2d.hpp>
#include <algorithm>
#include <limits>
#include "Random/Random.hpp"


Animal::Animal(const Vec2d& position)
    :   Collider(position, ANIMAL_RADIUS),
        speed (0.0),
        targetPosition (0, 0),
        direction (1, 0)
{}

double Animal::getStandardMaxSpeed()const
{
    return ANIMAL_MAX_SPEED;
}

double Animal::getMass()const
{
    return  ANIMAL_MASS;
}

void Animal::setTargetPosition (const Vec2d& newPosition)
{
    targetPosition = newPosition;
}

Vec2d Animal::getSpeedVector () const
{
    Vec2d res(direction.x()*speed,direction.y()*speed);
    return res;
}

void Animal::draw(sf::RenderTarget& targetWindow)const
{
    drawVision(targetWindow);
    sf::Texture& texture = getAppTexture(ANIMAL_TEXTURE);
    auto image_to_draw(buildSprite(this->getPosition(),
                                   (this->getRadius()*2),
                                   texture,
                                   getRotation() /DEG_TO_RAD));
    targetWindow.draw(image_to_draw);
    targetWindow.draw(buildCircle(targetPosition, 5.0, sf::Color(255, 0, 0)));

}

void Animal::setDecelerationMode(DecelerationMode mode)
{
    currentDeceleration = mode;
}

double Animal::getDeceleration(const DecelerationMode& mode) const
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



Vec2d Animal::getAttractionForce(const Vec2d& chosenTarget) const
{

    Vec2d res;

    Vec2d vectToTarget=chosenTarget-this->getPosition();

    if (vectToTarget.length() == 0) {
        return Vec2d(0, 0);
    }

    double wantedSpeed = std::min((vectToTarget.length()/currentDeceleration), getStandardMaxSpeed());

    Vec2d vTarget(vectToTarget*wantedSpeed/vectToTarget.length());

    res=vTarget-getSpeedVector();

    return res;
}

double Animal::getRandomWalkRadius() const
{
    return ANIMAL_RANDOM_WALK_RADIUS;
}

double Animal::getRandomWalkDistance() const
{
    return ANIMAL_RANDOM_WALK_DISTANCE;
}

double Animal::getRandomWalkJitter() const
{
    return ANIMAL_RANDOM_WALK_JITTER;
}

Vec2d Animal::convertToGlobalCoord(const Vec2d& local)const
{
    // create a transformation matrix
    sf::Transform matTransform;

    // first, translate
    matTransform.translate(getPosition());

    // then rotate
    matTransform.rotate(getRotation()/DEG_TO_RAD);

    // now transform the point
    Vec2d global = matTransform.transformPoint(local);
    return global;
}

void Animal::randomWalk(double elapsedTime)
{


    Vec2d random_vec (uniform(-1.0,1.0),uniform(-1.0,1.0));
    current_target += random_vec * getRandomWalkJitter();
    current_target = current_target.normalised()*getRandomWalkRadius();

    Vec2d moved_current_target = current_target + Vec2d(getRandomWalkDistance(), 0);

    Vec2d acceleration = getAttractionForce(convertToGlobalCoord(moved_current_target)) / getMass();

    Vec2d newSpeed = getSpeedVector() + acceleration * elapsedTime;

    if (newSpeed.length() > getStandardMaxSpeed()) {
        newSpeed = newSpeed.normalised() * getStandardMaxSpeed();
    }

    if (!isEqual(newSpeed.length(),0.0)) {
        direction = newSpeed.normalised();
        speed=newSpeed.length();
    }

    this->move(newSpeed*elapsedTime);
}

void Animal::update(sf::Time dt)
{

    //application de l'algorythme d'Euler-Cromer

    double elapsedTime = dt.asSeconds();

    std::list <Vec2d> targetsInSight = getAppEnv().getTargetsInSightForAnimal(this);

    if (!targetsInSight.empty()) {

        Vec2d chosenTarget(getClosestTarget(targetsInSight));

        setTargetPosition(chosenTarget);

        Vec2d acceleration = getAttractionForce(chosenTarget) / getMass();

        Vec2d newSpeed = getSpeedVector() + acceleration * elapsedTime;

        if (newSpeed.length() > getStandardMaxSpeed()) {
            newSpeed = newSpeed.normalised() * getStandardMaxSpeed();
        }

        if (!isEqual(newSpeed.length(),0.0)) {
            direction = newSpeed.normalised();
            speed=newSpeed.length();
        }

        this->move(newSpeed*elapsedTime);

    }

    else {

        this->randomWalk(elapsedTime);

    }



}


double Animal::getViewRange() const
{
    return ANIMAL_VIEW_RANGE;
}

double Animal::getViewDistance() const
{
    return ANIMAL_VIEW_DISTANCE;
}

double Animal::getRotation() const
{
    return direction.angle();
}

void Animal::setRotation(const double& angle)
{
    direction = {cos(angle), sin(angle)};
}

void Animal::drawVision(sf::RenderTarget& targetWindow)const
{

    sf::Color color = sf::Color::Black;
    color.a = 16; // light, transparent grey
    Arc arc(buildArc((-getViewRange()/2)/ DEG_TO_RAD, (getViewRange()/2)/DEG_TO_RAD, getViewDistance(), getPosition(), color, getRotation()/ DEG_TO_RAD));
    targetWindow.draw(arc);

    if (!isTargetInSight(targetPosition)) {

        targetWindow.draw(buildAnnulus(convertToGlobalCoord(Vec2d(getRandomWalkDistance(), 0)), getRandomWalkRadius(), sf::Color(255, 150, 0), 2));
        targetWindow.draw(buildCircle(convertToGlobalCoord(current_target + Vec2d(getRandomWalkDistance(), 0)), 5.0, sf::Color(0, 0, 255)));

    }


}

bool Animal::isTargetInSight(const Vec2d& wantedTargetPosition) const
{

    Vec2d animalToTarget = (wantedTargetPosition - getPosition());

    if (isEqual(animalToTarget.lengthSquared(), 0.0)) {
        return true;
    }

    return ((animalToTarget.lengthSquared() <= getViewDistance()*getViewDistance())
            and ((direction.dot(animalToTarget.normalised()))>= cos((getViewRange()+ 0.001)/2)));


}

Vec2d Animal::getClosestTarget(std::list <Vec2d> targetsInSight)const
{

    double minDistance(std::numeric_limits<double>::infinity());
    Vec2d closestTarget;

    for (const auto& target : targetsInSight) {

        if ((minDistance*minDistance)>(target - this->getPosition()).lengthSquared()) {
            minDistance=(target - this->getPosition()).length();
            closestTarget=target;
        }

    }

    return closestTarget;
}
