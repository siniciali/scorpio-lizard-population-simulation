#pragma once
#include "Obstacle/Collider.hpp"
#include <Utility/Vec2d.hpp>
#include "Animal/ChasingAutomaton.hpp"




/*!
 * @class Animal
 * @brief A simple automate that chases a target in a 2D environment.
 *
 * Inherits from Collider, meaning it also has a position and radius.
 * This class models an entity that can pursue a given target position
 * with a force-based approach and an Euler-Cromer update method.
 */

class Animal : public Collider
{

public:

    /*!
     * @brief Constructor for Animal.
     * Initializes the entity at a given position, with zero speed,
     * a default direction of (1, 0), and an empty target position.
     *
     * @param position The initial position of the Animal.
     */
    Animal(const Vec2d& position);

    /*!
     * @brief Sets the target position for the animal to chase.
     * @param newposition The new position of the target.
     */
    void setTargetPosition (const Vec2d& newposition);

    /*!
     * @brief Sets the deceleration mode for the animal.
     * Allows changing the deceleration factor externally (Strong, Medium, Weak).
     *
     * @param mode The DecelerationMode to use (e.g., Strong, Medium, Weak).
     */

    void setDecelerationMode(DecelerationMode mode);

    /*!
     * @brief Updates the animal position and speed over a time step.
     * Uses a force-based model (attraction force) and an Euler-Cromer integration.
     *
     * @param dt The time elapsed since the last update (in seconds).
     */

    void update(sf::Time dt);

    /*!
     * @brief Draws the animal and its target in the given window.
     * @param targetWindow The graphical window where the animal (and target) should be rendered.
     */

    void draw(sf::RenderTarget& targetWindow)const;

    double getViewRange() const;

    double getViewDistance() const;

    bool isTargetInSight(const Vec2d& wantedTargetPosition) const;

    double getRandomWalkRadius() const;

    double getRandomWalkDistance() const;

    double getRandomWalkJitter() const;

    Vec2d convertToGlobalCoord(const Vec2d& local)const;

    void randomWalk(double elapsedTime);


protected:

    double getRotation() const;

    void setRotation(const double& angle);


private:

    /*!
     * @brief The scalar speed of the animal (norm of its velocity).
     * Combined with #direction to produce the velocity vector.
     */
    double speed;

    /*!
    * @brief The current target position the animal is chasing.
    */

    Vec2d targetPosition;

    /*!
     * @brief The normalized direction of the animal movement.
     */

    Vec2d direction;

    Vec2d current_target;


    /*!
     * @brief Current deceleration mode used to modulate speed based on distance to target.
     */

    DecelerationMode currentDeceleration = Medium;

    /*!
     * @brief Converts a DecelerationMode into a numerical factor (0.3, 0.6, or 0.9).
     * @param mode The DecelerationMode to convert.
     * @return The deceleration factor associated with the given mode.
     */

    double getDeceleration(const DecelerationMode& mode) const;

    /*!
     * @brief Computes the attraction force towards the current target position,
     *        taking into account the current deceleration mode.
     *
     * If the distance to the target is zero, the force is zero.
     *
     * @return A vector representing the attraction force.
     */

    Vec2d getAttractionForce(const Vec2d& chosenTarget) const;

    /*!
     * @brief Getter for the animal's maximal speed, loaded from constants.
     * @return The animal's maximum allowed speed.
     */

    double getStandardMaxSpeed()const;

    /*!
     * @brief Getter for the animal's mass, loaded from constants.
     * @return The animal's mass.
     */

    double getMass() const;

    /*!
     * @brief Computes the velocity vector of the animal.
     * @return The current velocity vector of the animal.
     */

    Vec2d getSpeedVector () const;

    double viewRange;
    double viewDistance;

    void drawVision(sf::RenderTarget& targetWindow)const;

    Vec2d getClosestTarget(std::list <Vec2d> targetsInSight)const;



};
