#pragma once
#include <list>

#include "../Utility/Vec2d.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include <algorithm>

class OrganicEntity;
class Animal;
class CloudGenerator;
class Cloud;
class Wave;
class Collider;

class Environment : public Drawable, public Updatable
{
public:

    Environment();

    ~Environment();

    Environment(const Environment& autreEnvironnement) = delete;

    Environment& operator=(const Environment& autreEnvironnement) = delete;

    // contrôle température

    void increaseTemperature();

    double getTemperature() const;

    void decreaseTemperature();

    void resetControls();


    void addEntity(OrganicEntity* newentity);

    std::list <OrganicEntity*> getEntitiesInSightForAnimal(Animal* animal) const;

    void addGenerator(CloudGenerator* new_cloud_generator);

    void createCloud(const Vec2d& position, double radius);

    void update(sf::Time dt);

    void draw(sf::RenderTarget& targetWindow) const;

    void clean();

    sf::Time getDroughtTime() const;

    double getCloudNumber() const;

    //bool getRainingStatus() const;

    bool getHumidity() const;

    sf::Time getHumidityTime() const;

    void addWave(Wave* new_wave);
    void addObstacle(Collider* new_obstacle);
    double getIntensitySumAt(const Vec2d& location) const;

private:

    std::list <OrganicEntity*> entities;
    std::list <CloudGenerator*> cloud_generators;
    std::list<Cloud*> clouds;
    std::list<Wave*> waves;
    std::list<Collider*> obstacles;

    double temperature;

    sf::Time droughtTime;
    sf::Time rainingTime;
    sf::Time humidityTime;

    bool isRaining;
    bool isHumid;

    void modelizeRaining(sf::Time dt);
    void modelizeHumidity(sf::Time dt);

};
