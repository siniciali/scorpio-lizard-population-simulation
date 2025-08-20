#pragma once
#include "../Obstacle/Collider.hpp"
#include "../Utility/Vec2d.hpp"


/*!
 * @class ChasingAutomaton
 * @brief A simple automate that chases a target in a 2D environment.
 */

class ChasingAutomaton : public Collider
{

public:

    /*!
     * @brief Constructor for ChasingAutomaton.
     * Initializes the entity at a given position, with zero speed,
     * a default direction of (1, 0), and an empty target position.
     *
     * @param position The initial position of the ChasingAutomaton.
     */
    ChasingAutomaton(const Vec2d& position);

    ~ChasingAutomaton();

    /*!
     * @brief Updates the automaton's position and speed over a time step.
     * Uses a force-based model (attraction force) and an Euler-Cromer integration.
     *
     * @param dt The time elapsed since the last update (in seconds).
     */

    void update(sf::Time dt);

    /*!
     * @brief Draws the automaton and its target in the given window.
     * @param targetWindow The graphical window where the automaton (and target) should be rendered.
     */

    void draw(sf::RenderTarget& targetWindow)const;

private:

    /*!
     * @brief The scalar speed of the automaton (norm of its velocity).
     * Combined with #direction to produce the velocity vector.
     */
    double speed;


    /*!
    * @brief The current target position the automaton is chasing.
    */

    Vec2d targetPosition;

    /*!
     * @brief The normalized direction of the automaton's movement.
     */

    Vec2d direction;


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

    Vec2d getAttractionForce() const;

    /*!
     * @brief Getter for the automaton's maximal speed, loaded from constants.
     * @return The automaton's maximum allowed speed.
     */

    double getStandardMaxSpeed() const;

    /*!
     * @brief Getter for the automaton's mass, loaded from constants.
     * @return The automaton's mass.
     */


    double getMass() const;

    /*!
     * @brief Computes the velocity vector of the automaton.
     * @return The current velocity vector of the automaton.
     */

    Vec2d getSpeedVector () const;

    /*!
     * @brief Sets the target position for the automaton to chase.
     * @param newposition The new position of the target.
     */
    void setTargetPosition (const Vec2d& newposition);

    /*!
     * @brief Sets the deceleration mode for the automaton.
     * Allows changing the deceleration factor externally (Strong, Medium, Weak).
     *
     * @param mode The DecelerationMode to use (e.g., Strong, Medium, Weak).
     */

    void setDecelerationMode(DecelerationMode mode);


};
