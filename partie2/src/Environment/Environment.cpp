#include "../Application.hpp"
#include "../Animal/Animal.hpp"
#include "Environment.hpp"
#include "../Utility/Utility.hpp"
#include "../Utility/Vec2d.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void Environment::addAnimal(Animal* newanimal)
{

    faune.push_back(newanimal);

}

void Environment::addTarget(const Vec2d& newtarget)
{

    targets.push_back(newtarget);

}

void Environment::update(sf::Time dt)
{
    for (const auto& animal : faune) {

        animal->update(dt);

    }
}

void Environment::draw(sf::RenderTarget& targetWindow) const
{

    for (const auto& target : targets) {

        targetWindow.draw(buildCircle(target, 5.0, sf::Color(255, 0, 0)));
    }
    for (const auto& animal : faune) {
        animal->draw(targetWindow);
    }



}

void Environment::clean()
{

    for (auto& animal : faune) {
        delete animal;
    }

    while (!faune.empty()) {
        faune.pop_back();
    }

    while (!targets.empty()) {
        targets.pop_back();
    }
}

Environment::~Environment()
{
    clean();
}

std::list <Vec2d> Environment::getTargetsInSightForAnimal(Animal* animal) const
{

    std::list <Vec2d> targetsInSight;

    for (const auto& target : targets) {

        if(animal->isTargetInSight(target)) {

            targetsInSight.push_back(target);

        }

    }

    return targetsInSight;

}
