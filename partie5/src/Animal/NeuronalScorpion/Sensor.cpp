#include "../Animal/NeuronalScorpion/Sensor.hpp"
#include "../Animal/NeuronalScorpion/NeuronalScorpion.hpp"
#include "../Application.hpp"
#include "../Environment/Environment.hpp"

Sensor::Sensor(NeuronalScorpion* scorpion, size_t index)
    : associated_scorpion(scorpion),
      sensorIndex(index),
      isActive(false),
      score(0.0),
      inhibitor(0.0),
      sensibility_time(sf::Time::Zero),
      associated_sensors({nullptr, nullptr, nullptr})
{}

void Sensor::setInhibitor(double new_inhibitor)
{
    double max_inhibition = getAppConfig().sensor_inhibition_max;
    double new_inhibition = inhibitor + new_inhibitor;
    if(new_inhibition < 0.0) {
        return; // will keep previous value or default value (which is 0)
    }
    if(new_inhibition<max_inhibition) {
        inhibitor = new_inhibition;
    } else {
        inhibitor = max_inhibition;
    }
}

void Sensor::updateScore()
{
    // use of given inhibitor formula
    score += 2.0 * (1.0 - inhibitor);
}

void Sensor::update(sf::Time dt)
{
    // Activate if intensity exceeds threshold
    if (!isActive and
        getAppEnv().getIntensitySumAt(associated_scorpion->getPositionOfSensor(sensorIndex))
        >getAppConfig().sensor_intensity_threshold) {
        isActive = true;
    }

    if (isActive) {
        sensibility_time += dt;
        if (sensibility_time.asSeconds() >= getAppConfig().sensor_activation_duration) {
            // Set direction estimation after activation duration
            associated_scorpion->setDirectionEstimation();

            // Reset all sensors
            for (auto& sensor : associated_scorpion->getSensors()) {
                sensor.first->reinitialisation();
            }
            return;
        }

        updateScore();
        double new_inhibitor = score * getAppConfig().sensor_inhibition_factor;

        // propagate inhibition to associated sensors
        for (auto* sensor : associated_sensors) {
            if (sensor != nullptr) {
                sensor->setInhibitor(new_inhibitor);
            }
        }
    }
}

void Sensor::reinitialisation()
{
    score = 0;
    inhibitor = 0;
    sensibility_time = sf::Time::Zero;
    isActive = false;
}

void Sensor::addAssociatedSensors(Sensor* associated_sensor, size_t idx)
{
    associated_sensors[idx] = associated_sensor;
}

double Sensor::getScore() const
{
    return score;
}

bool Sensor::getIfActive() const
{
    return isActive;
}

sf::Color Sensor::getSensorColor() const
{
    // Return color based on activation and inhibition state
    if (isActive and inhibitor >= 0.2) {
        return sf::Color::Magenta;
    } else if (!isActive and inhibitor >= 0.2) {
        return sf::Color::Blue;
    } else if (isActive and inhibitor < 0.2) {
        return sf::Color::Red;
    } else {
        return sf::Color::Green;
    }
}
