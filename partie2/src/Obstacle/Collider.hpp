/*
 * POOSV 2025
 */

#pragma once

#include <Utility/Vec2d.hpp>
#include <SFML/Graphics.hpp>
#include <ostream>
#include <string>

/*!
 * @enum DecelerationMode
 * @brief Enumerates different deceleration modes that can be applied
 *        to a ChasingAutomaton and an Animal.
 *
 * - Strong:      Factor of 0.9, causing strong deceleration.
 * - Medium:      Factor of 0.6, for moderate speed deceleration.
 * - Weak:        Factor of 0.3, allowing higher speed with mild deceleration.
 */

enum DecelerationMode {Strong, Medium, Weak};

/*!
 * @brief A collider is defined by a radius
 * and a position in a toric world.
 *
 * @note radius must be >= 0.
 *
 * @note The "true" direction/distance denotes the
 * direction/distance for the shortest path between
 * the two considered points. (When considering a
 * body, we actually use its center as the source/
 * destination point.)
 */

class Collider
{
public:
    // public methods

    /*!
    * @brief Constructor for Collider. The position is adjusted using the ' clamping() ' method.
    *
    * @param positionCenter: The initial position of the collider in the toric world.
    * @param radius: The radius of the collider.
    *
    * @throws std::invalid_argument if the radius is negative.
    */

    Collider(const Vec2d& positionCenter, double radius);

    /*!
    * @brief Copy for Collider
    */

    Collider(const Collider& autreCollider);

    /*!
    * @brief Assignment operator.
    */
    Collider& operator=(const Collider& autreCollider);

    /*!
    * @brief Position getter
    * @return A constant reference to the position.
    */

    const Vec2d& getPosition() const;

    /*!
    * @brief Radius getter
    * @return The radius of the collider.
    */

    double getRadius() const;

    /*!
         * @brief Computes the shortest direction vector from this Collider to a given position in the toric world.
         * @param to The target position.
         * @return The shortest Vec2d direction vector.
         */
    Vec2d directionTo(const Vec2d& to) const;

    /*!
     * @brief Computes the shortest direction vector from this Collider to another Collider in the toric world.
     * @param other The Collider to compute the direction to.
     * @return The shortest Vec2d direction vector.
     */
    Vec2d directionTo(const Collider& autreCollider) const;

    /*!
     * @brief Computes the shortest distance from this Collider to a given position in the toric world.
     * @param to The target position.
     * @return The shortest distance.
     */
    double distanceTo(const Vec2d& to) const;

    /*!
     * @brief Computes the shortest distance from this Collider to another Collider in the toric world.
     * @param other The Collider to compute the distance to.
     * @return The shortest distance.
     */
    double distanceTo(const Collider& autreCollider) const;

    /*!
     * @brief Moves the Collider by a given displacement vector.
     * @param dx The displacement vector to add to the Collider's position.
     */
    void move(const Vec2d& dx);

    /*!
     * @brief Moves the Collider by a given displacement vector.
     * @param dx The displacement vector to add to the Collider's position.
     * @return A reference to the updated Collider.
     */
    Collider& operator+=(const Vec2d& dx);

    /*!
     * @brief Checks if the provided Collider is inside the current instance.
     * @param autreCollider The Collider that will be checked for being inside the current instance.
     * @return True if the Collider is inside; False otherwise.
     */
    bool isColliderInside (const Collider& autreCollider) const;

    /*!
     * @brief Checks if the provided Collider is colliding with the current instance.
     * @param autreCollider The Collider that will be checked for being in collision the current instance.
     * @return True if the Collider is colliding; False otherwise.
     */
    bool isColliding (const Collider& autreCollider) const;

    /*!
     * @brief Checks if the provided point is inside the current instance.
     * @param point The point (type Vec2d) that will be checked for being inside the current instance.
     * @return True if the point is inside; False otherwise.
     */
    bool isPointInside (const Vec2d& point) const;

    /*!
     * @brief Checks if the provided Collider is inside the current instance. (Surcharge d'operateur > )
     * @param point The Collider that will be checked for being inside the current instance.
     * @return True if the Collider is inside; False otherwise.
     */
    bool operator>(const Collider& autreCollider) const;

    /*!
     * @brief Checks if the provided Collider is colliding with the current instance. (Surcharge d'operateur | )
     * @param autreCollider The Collider that will be checked for being in collision the current instance.
     * @return True if the Collider is colliding; False otherwise.
     */
    bool operator|(const Collider& autreCollider) const;

    /*!
     * @brief Checks if the provided point is inside the current instance. (Surcharge d'operateur > )
     * @param point The Vec2d that will be checked for being inside than the current instance.
     * @return True if the point is inside; False otherwise.
     */
    bool operator>(const Vec2d& point) const;

private:
    // private attributes
    Vec2d positionCenter;
    double radius;

    // private methods

    /*!
    * @brief Adjusts the position of the collider within the toric world.
    */
    void clamping();
};

/*!
    * @brief Displays the attributes "positionCenter" and "radius" of the current instance (Surcharge d'operateur <<) with the form: "Collider: position = <positionCenter>, radius = <radius>".
    * @param sortie String stream in which the data are stored.
    * @param body Collider that will be displayed in said form.
    * @return reads sortie ad displays the informations of body.
    */
std::ostream& operator<< (std::ostream& sortie, Collider const& body);
