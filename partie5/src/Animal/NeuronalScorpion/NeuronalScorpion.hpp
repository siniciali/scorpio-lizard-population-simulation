#pragma once

#include "../Animal/Scorpion.hpp"

#include <array>

/**
 * @brief Defines the internal behavioral states of the NeuronalScorpion.
 */
enum currentStateNeuronalScorpion {

    IDLE,             ///< Passive scanning without moving
    TARGET_IN_SIGHT,  ///< Food directly visible
    MOVING,           ///< Moving toward estimated direction from sensor activation
    WANDERING_        ///< Random walk when no stimuli are present

};

// Fixed angular positions (in degrees) of the 8 sensors around the scorpion true for all NeuronalScorpion
class Sensor;
static constexpr std::array<double, 8> SENSOR_POSITIONS = {18, 54, 90, 140, -140, -90, -54, -18};


/**
 * @brief A scorpion variant controlled by eight directional sensors.
 *
 * This class models a predator that uses simulated perception via wave-activated sensors,
 * and transitions between multiple internal behavioral states depending on its sensory input.
 */
class NeuronalScorpion : public Scorpion
{
public:

    /**
     * @brief Constructors of NeuronalScorpion.
     */
    NeuronalScorpion(const Vec2d& initialPosition, double energyLvl, bool isFemale);
    NeuronalScorpion(const Vec2d& initialPosition);

    /**
     * @brief Destructor of NeuronalScorpion — deletes all dynamically allocated Sensor instances.
     */
    ~NeuronalScorpion() override;

    /**
     * @brief Computes the global position of a specific sensor based on its index.
     * @param chosen_sensor Index of the sensor (must be in [0, 7]).
     * @return The global position of the sensor in the environment.
     */
    Vec2d getPositionOfSensor(size_t chosen_sensor) const;

    /**
     * @brief Computes a direction vector from the weighted activation of all sensors.
     * @note Updates `direction_estimation` and `direction_estimation_score`.
     */
    void setDirectionEstimation();

    /**
     * @brief Updates the sensors, internal state, and movement accordingly.
     */
    void update(sf::Time dt) override;

    /**
     * @brief Draws sensors, state, and debug visuals for simulation.
     */
    void debuggingDisplay(sf::RenderTarget& targetWindow) const override;

    /**
    * @brief Increments the neuronal scorpion Counter in the environment.
    */
    void incrementCounter() const override final;


    /**
     * @brief Returns the internal array of sensors and their orientation.
     * @return An array of pairs, each containing a pointer to a Sensor and its orientation angle.
     */
    std::array<std::pair<Sensor*, double>,8> getSensors() const;

private:
    // === Sensor structure ===

    std::array<std::pair<Sensor*, double>,8> sensors; ///< Each sensor is paired with its angle
    Vec2d direction_estimation; ///< Vector pointing towards estimated wave source
    double direction_estimation_score; ///< Total score of the estimation

    Vec2d virtual_target; ///< Used to simulate a direction when no food is seen


    // === Internal state timers ===
    sf::Time idle_time;
    sf::Time moving_time;

    currentStateNeuronalScorpion current_state_ns;

    // === State helper methods ===
    void movingBehaviour(sf::Time dt);
    void idleBehaviour(sf::Time dt);

    void idleUpdateState();
    void movingUpdateState(sf::Time dt);

    bool isMoving = false;
    bool isIdle = false;

    /**
     * @brief Initializes all sensors and their mutual inhibitory connections.
     * @note There needs to be 2 loops so that all sensors already exist when we add the associated sensors.
     */
    void sensorConstruction();

    /**
     * @brief Updates the scorpion's internal behavioral state based on sensors and environment.
     */
    void updateState(sf::Time dt);

};
