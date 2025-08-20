#pragma once
#include <list>

#include "../Utility/Vec2d.hpp"
#include <SFML/Graphics.hpp>

/*!
 * @brief An Environment represents the simulated world in which entities such as animals and resources live.
 *
 *
 * This class provides basic methods to populate the environment, update its state over time, draw it,
 * and clean it when necessary.
 *
 * @note The Environment is not copyable (copy constructor and assignment operator are deleted).
 * @note The Environment manages the lifetime of its animals and ensures proper cleanup upon destruction.
 */

class Animal;

class Environment
{
public:


    /*!
    * @brief Default constructor for Environment.
    */
    Environment() = default;

    /*!
    * @brief Destructor that ensures all dynamically allocated animals are properly deleted.
    */
    ~Environment();


    /*!
    * @brief Copy constructor is deleted to prevent copies of environments.
    */
    Environment(const Environment& autreEnvironnement) = delete;

    /*!
    * @brief Assignment operator is deleted to prevent copies of environments.
    */
    Environment& operator=(const Environment& autreEnvironnement) = delete;

    /*!
    * @brief Adds an animal to the environment.
    *
    * @param newanimal Pointer to the dynamically allocated animal to add.
    */
    void addAnimal(Animal* newanimal);

    /*!
    * @brief Adds a new resource target at the specified position.
    *
    * @param newtarget Position (Vec2d) of the new resource to add.
    */
    void addTarget(const Vec2d& newtarget);

    /*!
    * @brief Updates the state of the environment.
    *
    *
    * @param dt Time step since the last update.
    */
    void update(sf::Time dt);

    /*!
    * @brief Draws the environment to the provided SFML render target.
    *
    *
    * @param targetWindow The SFML render target.
    */
    void draw(sf::RenderTarget& targetWindow) const;

    /*!
    * @brief Clears the environment by removing all animals and targets.
    *
    * All dynamically allocated animals are deleted, and the internal lists are emptied.
    */
    void clean();

    std::list <Vec2d> getTargetsInSightForAnimal(Animal* animal)const;

private:
    /*!
    * @brief List of animal pointers currently living in the environment.
    */
    std::list <Animal*> faune;

    /*!
    * @brief List of resource target positions in the environment.
    */
    std::list <Vec2d> targets;

};
