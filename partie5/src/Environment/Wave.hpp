#pragma once

#include "../Obstacle/Collider.hpp"
#include <list>

/**
 * @brief Represents a propagating wave in the simulation.
 *
 * The Wave class models a circular wave that expands over time,
 * loses energy, and can be fragmented by obstacles.
 */
class Wave : public Collider
{

public:
    /**
     * @brief Constructs a wave with given parameters.
     * @param origin The center position of the wave.
     * @param initial_energy The initial energy of the wave.
     * @param initial_radius The starting radius of the wave.
     * @param mu The attenuation coefficient.
     * @param speed The propagation speed of the wave.
     */
    Wave(const Vec2d& origin,
         double initial_energy,
         double initial_radius,
         double mu,
         double speed);

    /**
     * @brief Destructor for the Wave class.
     */
    ~Wave();

    /**
     * @brief Gets the attenuation coefficient.
     * @return The mu value.
     */
    double getMu() const;

    /**
     * @brief Gets the wave's propagation speed.
     * @return The speed of the wave.
     */
    double getPropagationSpeed() const;

    /**
     * @brief Updates the wave's state over time.
     * @param dt Time elapsed since the last update.
     */
    void update(sf::Time dt) override final;

    /**
     * @brief Draws the wave on the render target.
     * @param targetWindow The window to draw the wave on.
     */
    void draw(sf::RenderTarget& targetWindow) const override final;

    /**
     * @brief Gets the current intensity of the wave.
     * @return The wave's intensity.
     */
    double getIntensity() const;

    /**
     * @brief Fragments the wave when it encounters an obstacle.
     * @param obstacle The collider causing the fragmentation.
     */
    void fragmentWave(const Collider& obstacle);

    /**
     * @brief Gets the list of arcs representing the wave's visible segments.
     * @return A list of angle pairs (start, end) in radians.
     */
    std::list<std::pair<double, double>> getArcs() const;

    /**
     * @brief Checks if an angle lies within a given arc.
     * @param obstacle_angle The angle to check.
     * @param arc The arc to test against.
     * @return True if the angle is within the arc.
     */
    bool isAngleInArc(double obstacle_angle, const std::pair<double, double>& arc) const;

private:
    const double initial_energy; ///< Initial energy of the wave.
    const double initial_radius; ///< Starting radius of the wave.
    const double mu; ///< Attenuation coefficient.
    const double propagation_speed; ///< Speed at which the wave expands.
    double current_radius; ///< Current radius of the wave.
    double current_energy; ///< Current energy of the wave.
    double current_intensity; ///< Current intensity of the wave.
    double elapsed_time; ///< Time since the wave started.
    std::list<std::pair<double, double>> arcs; ///< List of visible arcs (angle ranges).
};


