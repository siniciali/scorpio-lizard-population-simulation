#include "../Application.hpp"
#include "../Animal/Animal.hpp"
#include "Environment.hpp"
#include "../Utility/Utility.hpp"
#include "../Utility/Vec2d.hpp"
#include <SFML/Graphics.hpp>
#include "../Environment/Cloud.hpp"
#include "../Environment/Wave.hpp"
#include "Obstacle/Collider.hpp"
#include "../Environment/CloudGenerator.hpp"
#include "../Random/Random.hpp"
#include <algorithm>


Environment::Environment()
    : temperature(getAppConfig().environment_default_temperature),
      droughtTime(sf::Time::Zero),
      isRaining(false),
      isHumid(false)
{}

Environment::~Environment()
{
    // Manual cleanup to prevent memory leaks
    clean();
}

double Environment::getTemperature() const
{
    return temperature;
}

void Environment::increaseTemperature()
{
    if (temperature+0.5<=getAppConfig().environment_max_temperature) {
        temperature+=0.5;
    } else {
        temperature=getAppConfig().environment_max_temperature;
    }
}


void Environment::decreaseTemperature()
{
    if (temperature - 0.5 >= getAppConfig().environment_min_temperature) {
        temperature -= 0.5;
    } else {
        temperature = getAppConfig().environment_min_temperature;
    }
}

void Environment::resetControls()
{
    temperature=getAppConfig().environment_default_temperature;
}

void Environment::addEntity(OrganicEntity* newentity)
{
    entities.push_back(newentity);
}

sf::Time Environment::getDroughtTime() const
{
    return droughtTime;
}

void Environment::addGenerator(CloudGenerator* new_cloud_generator)
{
    cloud_generators.push_back(new_cloud_generator);
}

void Environment::createCloud(const Vec2d& position, double radius)
{
    clouds.push_back(new Cloud(position, radius));
}

void Environment::waveUpdate(sf::Time dt)
{
    // First loop: update and fragment waves on collisions
    for (auto* wave : waves) {
        for (const auto* obstacle : obstacles) {
            if (wave->isColliding(*obstacle)) {
                wave->fragmentWave(*obstacle);
            }
        }
        wave->update(dt);
    }
    // Second loop: delete low-intensity waves
    for (auto& wave : waves) {
        if (wave->getIntensity() < getAppConfig().wave_intensity_threshold) {
            delete wave;
            wave = nullptr;
        }
    }

    waves.erase(std::remove(waves.begin(), waves.end(), nullptr), waves.end());
}

void Environment::entityUpdate(sf::Time dt)
{

    for (const auto& entity : entities) {
        entity->update(dt);
    }

    for (auto& entity : entities) {
        if (entity->isDead()) {
            delete entity;
            entity = nullptr;
        }
    }
    entities.erase(std::remove(entities.begin(), entities.end(), nullptr), entities.end());

}

void Environment::cloudUpdate(sf::Time dt)
{

    if (clouds.empty()) {
        droughtTime += dt;
    }

    for (auto& cloud : clouds) {
        cloud->update(dt);
    }

    for (auto& cloud : clouds) {
        if (cloud != nullptr
            and cloud->getEvaporationState()) {
            delete cloud;
            cloud = nullptr;
        }
    }

    clouds.erase(
        std::remove(clouds.begin(), clouds.end(), nullptr),
        clouds.end()
    );

    for (auto& generator : cloud_generators) {
        generator->update(dt);
    }
}

void Environment::countersUpdate()
{
    // we must reinitialize to 0 because we count at each frame the number
    // of each species currently present in the envrionment
    scorpionCounter=0;
    lizardCounter=0;
    cactusCounter=0;
    NSCounter=0;
    WLCounter=0;

    for (const OrganicEntity* entity : entities) {
        entity->incrementCounter();
    }
}

void Environment::update(sf::Time dt)
{
    waveUpdate(dt);
    entityUpdate(dt);
    modelizeRaining(dt);
    cloudUpdate(dt);
    if (isHumid) {
        modelizeHumidity(dt);
    }
    countersUpdate();
}

double Environment::getCloudNumber() const
{
    return clouds.size();
}

void Environment::draw(sf::RenderTarget& targetWindow) const
{

    // entities est le vector des OrganicEntity de l'encironnement,on en crée une copie dans une liste:
    std::list<OrganicEntity*> sorted(entities.begin(), entities.end());
    // on définit une relation d'ordre sur la base de getDepth():
    auto comp([](OrganicEntity* a, OrganicEntity* b)->bool{ return int(a->getDepth()) < int(b->getDepth()); });
    // on trie l'ensemble sur cette base
    sorted.sort(comp);
    // il faut ensuite dessiner l'ensemble trié sorted et non plus entities

    // Draw sorted organic entities
    for (const auto& entity : sorted) {
        entity->draw(targetWindow);
    }

    for (const auto& cloud : clouds) {
        cloud->draw(targetWindow);
    }

    for (const auto& wave : waves) {
        wave->draw(targetWindow);
    }

    for (const auto& obstacle : obstacles) {
        obstacle->draw(targetWindow);
    }

}

void Environment::clean()
{
    // Properly delete all dynamically allocated pointers
    for (auto& entity : entities) {
        delete entity;
    }
    entities.clear();

    for (auto& generator : cloud_generators) {
        delete generator;
    }
    cloud_generators.clear();

    for (auto& cloud : clouds) {
        delete cloud;
    }
    clouds.clear();

    for (auto& wave : waves) {
        delete wave;
    }
    waves.clear();

    for (auto& obstacle : obstacles) {
        delete obstacle;
    }
    obstacles.clear();
}

std::list <OrganicEntity*> Environment::getEntitiesInSightForAnimal(Animal* animal) const
{
    std::list <OrganicEntity*> entitiesInSight;

    for (const auto& entity_target : entities) {

        if(animal->isTargetInSight(entity_target->getPosition())) {

            entitiesInSight.push_back(entity_target);
        }
    }
    return entitiesInSight;
}

void Environment::modelizeRaining(sf::Time dt)
{
    if (!isRaining
        and (getCloudNumber()/getAppConfig().environment_max_clouds)>getAppConfig().environment_raining_cloud_density
        and bernoulli(getAppConfig().environment_raining_probability)) {
        isRaining=true;
        isHumid=false;
        rainingTime=sf::Time::Zero;
    }

    if(isRaining) {
        rainingTime += dt;
        for (auto& cloud : clouds) {
            Vec2d new_position(uniform(-1.0, 1.0), uniform(-1.0, 1.0));
            cloud->move(new_position);
        }
        // End of rain: evaporate all clouds
        if (rainingTime >= sf::seconds(getAppConfig().environment_raining_duration)) {
            isRaining = false;
            for (auto& cloud : clouds) {
                delete cloud;
            }
            while (!clouds.empty()) {
                clouds.pop_back();
            }
            droughtTime = sf::Time::Zero;
            isHumid = true;
            humidityTime = sf::Time::Zero;
        }
    }
}

void Environment::modelizeHumidity(sf::Time dt)
{
    if (isHumid) {
        humidityTime+=dt;
        if (humidityTime >= sf::seconds(getAppConfig().environment_humidity_duration)) {
            isHumid=false;
            humidityTime = sf::Time::Zero;
        }
    }
}

bool Environment::getHumidity() const
{
    return isHumid;
}

void Environment::addWave(Wave* new_wave)
{
    waves.push_back(new_wave);
}

void Environment::addObstacle(Collider* new_obstacle)
{
    obstacles.push_back(new_obstacle);
}

double Environment::getIntensitySumAt(const Vec2d& location) const
{
    double res = 0.0;
    double error_value = getAppConfig().wave_on_wave_marging;

    for (const auto* wave : waves) {
        Vec2d distance_vector=location - wave->getPosition();
        double angle = distance_vector.angle();
        double location_radius = distance_vector.length();
        double wave_radius = wave->getRadius();
        bool isAngleInside = false;

        for (const auto& arc : wave->getArcs()) {
            if (wave->isAngleInArc(angle, arc)) {
                isAngleInside = true;
                break;                         // inutile de continuer
            }
        }

        if(wave_radius >= location_radius - error_value
           and wave_radius <= location_radius + error_value
           and isAngleInside) {
            res += wave->getIntensity();
        }
    }
    return res;
}

std::unordered_map<std::string, double> Environment::fetchData(const std::string& title) const
{
    if (title == s::GENERAL) {
        return {
            {s::SCORPIONS, scorpionCounter},
            {s::LIZARDS, lizardCounter},
            {s::CACTUSES, cactusCounter}
        };
    } else if (title == s::WAVES) {
        return {
            {s::WAVES, waves.size()},
            {s::NEURONALSCORPION, NSCounter},
            {s::WAVELIZARD, WLCounter},
            {s::CACTUSES, cactusCounter}
        };
    }
    return {};
}

void Environment::incrementScorpionCounter()
{
    scorpionCounter++;
}

void Environment::incrementLizardCounter()
{
    lizardCounter++;
}

void Environment::incrementCactusCounter()
{
    cactusCounter++;
}

void Environment::incrementNS()
{
    NSCounter++;
}
void Environment::incrementWL()
{
    WLCounter++;
}

