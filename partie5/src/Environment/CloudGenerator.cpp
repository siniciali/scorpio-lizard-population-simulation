#include "../Environment/CloudGenerator.hpp"
#include "../Application.hpp"
#include "../Environment/Cloud.hpp"
#include "Random/Random.hpp"
#include "Environment/Environment.hpp"

CloudGenerator::CloudGenerator()
    : tcounter(sf::Time::Zero) // Initialize timer
{}

CloudGenerator::~CloudGenerator() {}

void CloudGenerator::update(sf::Time dt)
{
    tcounter += dt;

    // Check if it's time to attempt cloud generation
    if (tcounter >= sf::seconds(getAppConfig().cloud_generator_delta)) {
        tcounter = sf::Time::Zero;

        // Check environmental conditions for cloud creation
        if (getAppEnv().getDroughtTime() >= sf::seconds(getAppConfig().environment_drought_duration) and
            getAppEnv().getTemperature() <= getAppConfig().environment_rain_temperature and
            getAppEnv().getCloudNumber() < getAppConfig().environment_max_clouds) {

            // Generate a random position using normal distribution without having to copy two
            // times the values on variance and mu
            double mu = getAppConfig().simulation_world_size / 2.0;
            double variance = std::pow(getAppConfig().simulation_world_size / 4.0, 2);

            Vec2d positionCenter(
                normal(mu, variance),
                normal(mu, variance)
            );

            // Create a cloud with random size within configured bounds
            getAppEnv().createCloud(positionCenter,
                                    uniform(getAppConfig().cloud_min_size,
                                            getAppConfig().cloud_max_size));
        }
    }
}
