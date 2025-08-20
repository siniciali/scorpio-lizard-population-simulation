#pragma once
#include <array>
#include "SFML/Graphics.hpp"
#include "../Interface/Updatable.hpp"

class NeuronalScorpion;

/**
 * @brief Represents a sensory unit for a NeuronalScorpion.
 *
 * A Sensor detects wave intensity at its position, accumulates a score,
 * and can inhibit other sensors. It activates when intensity exceeds a threshold.
 */
class Sensor : public Updatable
{
public:
    /**
     * @brief Constructs a Sensor associated with a scorpion and index.
     * @param scorpion Pointer to the owning NeuronalScorpion.
     * @param index Index of the sensor on the scorpion.
     */
    Sensor(NeuronalScorpion* scorpion, size_t index);

    /**
     * @brief Default destructor.
     */
    ~Sensor() = default;

    /**
     * @brief Returns the current score of the sensor.
     */
    double getScore() const;

    /**
     * @brief Updates the score based on current inhibition.
     */
    void updateScore();

    /**
     * @brief Updates the sensor's state and activation logic.
     * @param dt Time elapsed since last update.
     */
    void update(sf::Time dt) override;

    /**
     * @brief Adds a sensor to the list of associated (inhibitable) sensors.
     * @param associated_sensor Pointer to the sensor to associate.
     * @param idx Index in the association array.
     */
    void addAssociatedSensors(Sensor* associated_sensor, size_t idx);

    /**
     * @brief Checks if the sensor is currently active.
     */
    bool getIfActive() const;

    /**
     * @brief Returns the color representing the sensor's state.
     */
    sf::Color getSensorColor() const;

private:
    // once initilaised, the pointer becomes const, it can only point towards the associated scorpion
    NeuronalScorpion* const associated_scorpion; ///< Pointer to the owning scorpion.
    const size_t sensorIndex; ///< Index of the sensor on the scorpion.

    bool isActive; ///< Whether the sensor is currently active.
    double score; ///< Accumulated score.
    double inhibitor; ///< Inhibition level.

    sf::Time sensibility_time; ///< Time since activation.

    std::array<Sensor*, 3> associated_sensors; ///< Sensors to inhibit.

    /**
     * @brief Resets the sensor to its initial state.
     */
    void reinitialisation();

    /**
     * @brief Sets the inhibition level, clamped to a maximum.
     * @param new_inhibitor The new inhibition value to apply.
     */
    void setInhibitor(double new_inhibitor);
};
