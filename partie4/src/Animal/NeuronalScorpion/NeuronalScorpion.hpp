#pragma once

#include "../Animal/Scorpion.hpp"

#include <array>

enum currentStateNeuronalScorpion {

    IDLE,  // au repos
    TARGET_IN_SIGHT, // proie en vue
    MOVING,  // ne voit pas proie mais l'a perçue à travers les ondes émises
    WANDERING_

};

class Sensor;
const std::array<double, 8> SENSOR_POSITIONS = {18, 54, 90, 140, -140, -90, -54, -18};


class NeuronalScorpion : public Scorpion
{
public:

    NeuronalScorpion(const Vec2d& initialPosition, double energyLvl, bool isFemale);
    NeuronalScorpion(const Vec2d& initialPosition);
    ~NeuronalScorpion() override;
    Vec2d getPositionOfSensor(size_t chosen_sensor) const;

    void setDirectionEstimation();

    void update(sf::Time dt) override;
    void updateState(sf::Time dt);
    void debuggingDisplay(sf::RenderTarget& targetWindow) const override; // à compléter

    std::array<std::pair<Sensor*, double>,8> getSensors()const;

private:

    std::array<std::pair<Sensor*, double>,8> sensors;
    Vec2d direction_estimation;
    double direction_estimation_score;

    Vec2d virtual_target;

    sf::Time sensor_activation;
    sf::Time idle_time;
    sf::Time moving_time;

    currentStateNeuronalScorpion current_state_ns;

    void movingBehaviour(sf::Time dt);
    void idleBehaviour(sf::Time dt);

    bool isMoving = false;
    bool isIdle = false;

    void sensorConstruction(); //fonction complémentaire servant à initialiser les pairs de senseurs et leur position respective

};
