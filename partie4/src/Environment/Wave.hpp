#pragma once

#include "../Obstacle/Collider.hpp"
#include "../Utility/Utility.hpp"
#include <list>



class Wave : public Collider
{

public:

    Wave(const Vec2d& origin,
         double initial_energy,
         double initial_radius,
         double mu,
         double speed);
    ~Wave();
    double getMu() const;
    double getPropagationSpeed() const;

    void update(sf::Time dt) override;
    void draw (sf::RenderTarget& targetWindow) const override;

    double getIntensity() const;

    void fragmentWave(const Collider& obstacle);

    std::list <std::pair<double, double>> getArcs() const;

    bool isAngleInArc(double obstacle_angle, std::pair<double, double> arc) const;


private:

    double initial_energy;
    double initial_radius;
    double mu;
    double propagation_speed;
    double current_radius;
    double current_energy;
    double current_intensity;
    double elapsed_time;
    std::list <std::pair<double, double>> arcs;

};
