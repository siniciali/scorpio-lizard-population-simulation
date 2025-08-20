/*
 * POOSV 2025
 */

/*
 * POOSV 2025
 */

#include "../Application.hpp"
#include "../Obstacle/Collider.hpp"
#include "../Utility/Utility.hpp"
#include "../Utility/Vec2d.hpp"
#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <limits>
#include <array>

Collider::Collider(const Vec2d& positionCenter, double radius)
    : positionCenter(positionCenter), radius(radius)
{

    if (radius < 0) {
        throw std::invalid_argument("Error: the radius connot be negative.");
    }

    clamping();
}

Collider::Collider(const Collider& autreCollider)
    : positionCenter(autreCollider.positionCenter), radius(autreCollider.radius) {}

Collider& Collider::operator=(const Collider& autreCollider)
{

    positionCenter = autreCollider.positionCenter;
    radius = autreCollider.radius;
    return *this;
}

Collider::~Collider()
{

}

void Collider::clamping()
{

    double worldSize = getAppConfig().simulation_world_size;
    auto width  = worldSize;
    auto height = worldSize;

    while (positionCenter.x()<0) {
        // We must define the modification of the x coordinate this way because it is defined as ' double x() const '
        // Therefore, we cannot modify it directly.
        positionCenter = Vec2d(positionCenter.x() + width, positionCenter.y());
    }

    while (positionCenter.x()>width) {
        positionCenter = Vec2d(positionCenter.x() - width, positionCenter.y());
    }

    while (positionCenter.y()<0) {
        positionCenter = Vec2d(positionCenter.x(), positionCenter.y() + height);
    }

    while (positionCenter.y()>height) {
        positionCenter = Vec2d(positionCenter.x(), positionCenter.y() - height);
    }
}

const Vec2d& Collider::getPosition() const
{
    return positionCenter;
}

double Collider::getRadius() const
{
    return radius;
}

Vec2d Collider::directionTo(const Vec2d& to) const
{
    double worldSize = getAppConfig().simulation_world_size;
    auto width  = worldSize;
    auto height = worldSize;
    Vec2d from = positionCenter;
    std::array<Vec2d, 9> candidates = {to,
        {to.x(), to.y()+ height},
        {to.x(), to.y()-height},
        {to.x()+width, to.y()},
        {to.x()-width, to.y()},
        {to.x()+width, to.y()+height},
        {to.x()+width, to.y()-height},
        {to.x()-width, to.y()+height},
        {to.x()-width, to.y()-height},
    };
    Vec2d goodCandidate(0,0);
    double distanceToChoose(std::numeric_limits<double>::infinity());

    for (size_t i(0); i<9; i++) {

        if (distanceToChoose > distance(candidates[i],from)) {
            distanceToChoose=distance(candidates[i],from);
            goodCandidate=candidates[i];
        }

    }

    return goodCandidate - from;

}

Vec2d Collider::directionTo(const Collider&autreCollider) const
{
    return directionTo(autreCollider.getPosition());
}

double Collider::distanceTo(const Vec2d& to) const
{
    return directionTo(to).length();
}

double Collider::distanceTo(const Collider& autreCollider) const
{
    return directionTo(autreCollider.getPosition()).length();
}

void Collider::move(const Vec2d& dx)
{

    positionCenter = positionCenter + dx;
    clamping();

}

Collider& Collider::operator+=(const Vec2d& dx)
{
    positionCenter = positionCenter + dx;
    clamping();
    return *this;
}

bool Collider::isColliderInside (const Collider& autreCollider) const
{
    return ((this->radius >= autreCollider.radius) and (distanceTo(autreCollider)<=(this->radius - autreCollider.radius)));
}

bool Collider::isColliding (const Collider& autreCollider) const
{
    return (distanceTo(autreCollider)<=(this->radius + autreCollider.radius));
}

bool Collider::isPointInside (const Vec2d& point) const
{
    return (distanceTo(point)<= this->radius);
}

bool Collider::operator>(const Collider& autreCollider)const
{
    return isColliderInside(autreCollider);;
}

bool Collider::operator|(const Collider& autreCollider) const
{
    return isColliding(autreCollider);
}

bool Collider::operator>(const Vec2d& point) const
{
    return isPointInside(point);
}

std::ostream& operator<< (std::ostream& sortie, Collider const& body)
{
    sortie << "Collider: position = " << body.getPosition() << ", radius = " << body.getRadius();
    return sortie;
}


