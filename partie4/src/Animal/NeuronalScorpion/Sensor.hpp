#pragma once
#include <array>
#include "SFML/Graphics.hpp"
#include "../Interface/Updatable.hpp"

class NeuronalScorpion;
class Wave;

class Sensor : public Updatable
{
public:
    Sensor(NeuronalScorpion* scorpion, size_t index);
    ~Sensor() = default;

    double getScore() const;

    void updateScore();

    void update(sf::Time dt) override;

    void addAssociatedSensors(Sensor* associated_sensor, size_t idx);

    bool getIfActive() const;
    //double getInhibitor() const;
    sf::Color getSensorColor();
    void reinitialisation();


private:
    NeuronalScorpion* associated_scorpion;
    size_t index; //index du senseur

    bool isActive;
    double score;
    double inhibitor;

    sf::Time sensibility_time;

    std::array<Sensor*,3> associated_sensors;



    void setInhibitor(double new_inhibitor);
};
