#include <Environment/CloudGenerator.hpp>
#include "../Application.hpp"
#include "Environment/Cloud.hpp"
#include "Random/Random.hpp"
#include "Environment/Environment.hpp"

CloudGenerator::CloudGenerator()
    : tcounter (sf::Time::Zero)
{}

CloudGenerator::~CloudGenerator() {}

void CloudGenerator::update(sf::Time dt)
{

    tcounter += dt;

    if (tcounter >= sf::seconds(getAppConfig().cloud_generator_delta)) {
        tcounter = sf::Time::Zero;

        if(getAppEnv().getDroughtTime() >= sf::seconds(getAppConfig().environment_drought_duration)
           and getAppEnv().getTemperature() <= getAppConfig().environment_rain_temperature
           and getAppEnv().getCloudNumber() < getAppConfig().environment_max_clouds)

        {

            double mu = getAppConfig().simulation_world_size / 2.0;
            double variance = (getAppConfig().simulation_world_size / 4.0)
                              * (getAppConfig().simulation_world_size / 4.0);

            Vec2d positionCenter(
                normal(mu, variance),
                normal(mu, variance)
            );

            getAppEnv().createCloud(positionCenter, uniform(getAppConfig().cloud_min_size, getAppConfig().cloud_max_size));

        }


    }

}
