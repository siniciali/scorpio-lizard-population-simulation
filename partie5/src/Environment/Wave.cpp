#include "../Environment/Wave.hpp"
#include <cmath>
#include "../Utility/Utility.hpp"
#include "../Utility/Constants.hpp"
#include "../Application.hpp"

Wave::Wave(const Vec2d& origin, double initial_energy, double initial_radius, double mu, double speed) :
    Collider(origin, initial_radius),
    initial_energy(initial_energy),
    initial_radius(initial_radius),
    mu(mu),
    propagation_speed(speed),
    current_radius(initial_radius),
    current_energy(initial_energy),
    current_intensity(initial_energy / (2 * PI * initial_radius)),
    elapsed_time(0.0)
{
    // Initialize with a full circle arc
    arcs.push_back(std::make_pair(-PI, PI));
}

Wave::~Wave() {}

double Wave::getMu() const
{
    return mu;
}

double Wave::getPropagationSpeed() const
{
    return propagation_speed;
}

void Wave::update(sf::Time dt)
{
    // Update time and radius
    elapsed_time += dt.asSeconds();
    current_radius = propagation_speed * elapsed_time + initial_radius;
    this->setRadius(current_radius);

    // Update energy and intensity using exponential decay
    current_energy = initial_energy * exp(-current_radius / mu);
    current_intensity = current_energy / (2 * PI * current_radius);
}

void Wave::draw(sf::RenderTarget &targetWindow) const
{
    for (const auto& arc : arcs) {
        // Convert arc angles to degrees and draw the arc
        auto image_to_draw = buildArc(
                                 arc.first * 180 / PI,
                                 arc.second * 180 / PI,
                                 current_radius,
                                 this->getPosition(),
                                 sf::Color::Black,
                                 0.0,
                                 current_intensity * getAppConfig().wave_intensity_thickness_ratio
                             );
        targetWindow.draw(image_to_draw);
    }
}

double Wave::getIntensity() const
{
    return current_intensity;
}

void Wave::fragmentWave(const Collider& obstacle)
{
    // Compute angle and angular width of the obstacle
    double obstacle_angle = (obstacle.getPosition() - this->getPosition()).angle();

    double R = current_radius;
    double r = obstacle.getRadius();
    double alpha = 2*std::atan2(r,R+r);

    std::list<std::pair<double,double>> newArcs;

    for (const auto& arc : arcs) {

        // Obstacle not in arc: keep arc unchanged
        if(obstacle_angle<=arc.first or obstacle_angle>=arc.second) {
            newArcs.emplace_back(arc.first,arc.second);
            continue;
        }

        // Obstacle is inside the arc: split it
        if(obstacle_angle-alpha/2>arc.first) {
            newArcs.emplace_back(arc.first,obstacle_angle-alpha/2);
        }
        if(obstacle_angle+alpha/2<arc.second) {
            newArcs.emplace_back(obstacle_angle+alpha/2,arc.second);
        }
    }

    // Replace old arcs with the new fragmented ones
    arcs.swap(newArcs);
}

std::list<std::pair<double, double>> Wave::getArcs() const
{
    return arcs;
}

bool Wave::isAngleInArc(double obstacle_angle, const std::pair<double, double>& arc) const
{
    if (arc.first <= arc.second)
        return (obstacle_angle >= arc.first and obstacle_angle <= arc.second);

    // Handle wrap-around arcs
    return (obstacle_angle >= arc.first or obstacle_angle <= arc.second);
}



