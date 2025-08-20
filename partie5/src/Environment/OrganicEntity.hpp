#pragma once
#include "../Obstacle/Collider.hpp"
#include "../Utility/Vec2d.hpp"

class Scorpion;
class Lizard;
class Cactus;

/**
 * @brief Abstract base class for all organic entities in the simulation.
 *
 * OrganicEntity represents living entities that have energy, age, and can interact
 * with other entities through eating, mating, or other behaviors.
 */
class OrganicEntity : public Collider
{

public:
    /**
     * @brief Constructs an organic entity with position, size, and energy level.
     * @param position Position of the entity.
     * @param size Diameter of the entity.
     * @param energyLvl Initial energy level.
     */
    OrganicEntity(const Vec2d& position, double size, double energyLvl);

    /**
     * @brief Virtual destructor for proper cleanup of derived classes.
     */
    virtual ~OrganicEntity();

    /**
     * @brief Gets the texture name for rendering.
     * @return A reference to the texture string.
     */
    virtual std::string getTextureName() const = 0;

    /**
     * @brief Updates the entity's state over time.
     * @param age Time elapsed since last update.
     */
    void update(sf::Time age) override;

    /**
     * @brief Determines if another entity is edible.
     * @param other Pointer to the other organic entity.
     * @return True if edible.
     */
    virtual bool eatable(const OrganicEntity* other) const = 0;

    virtual bool eatableDispatch(const Scorpion* scorpion) const = 0;
    virtual bool eatableDispatch(const Lizard* lizard) const = 0;
    virtual bool eatableDispatch(const Cactus* food) const = 0;

    /**
     * @brief Determines if this entity can mate with another.
     */
    virtual bool matable(OrganicEntity const* other) const = 0;

    virtual bool matableDispatch(Scorpion const* scorpion) const = 0;
    virtual bool matableDispatch(Lizard const* lizard) const = 0;
    virtual bool matableDispatch(Cactus const* food) const = 0;

    /**
     * @brief Checks if the entity is currently able to reproduce.
     * @return True if reproduction is possible.
     */
    virtual bool getIfCanReproduce() const = 0;

    /**
     * @brief Handles interaction with another organic entity.
     */
    virtual void meet(OrganicEntity* entity) = 0;
    virtual void meetDispatch(Lizard* lizard) = 0;
    virtual void meetDispatch(Scorpion* scorpion) = 0;
    virtual void meetDispatch(Cactus* cactus) = 0;

    /**
     * @brief Pure Virtual method that increments the counter polymorphically.
     */
    virtual void incrementCounter() const = 0;

    /**
     * @brief Gets the current energy level.
     */
    double getEnergyLevel() const;

    /**
     * @brief Sets the energy level.
     */
    void setEnergyLevel(const double& newenergy);

    /**
     * @brief Gets the total lifetime of the entity.
     */
    sf::Time getLifetime() const;

    /**
     * @brief Gets the minimum energy threshold before death.
     */
    double getEntityMinEnergy() const;

    /**
     * @brief Updates the lifetime by a time increment.
     */
    void updateLifetime(sf::Time dt);

    /**
     * @brief Checks if the entity is too weak to survive.
     */
    bool isTooWeak() const;

    /**
     * @brief Checks if the entity has exceeded its lifespan.
     */
    bool isTooOld() const;

    /**
     * @brief Checks if the entity is dead.
     */
    bool isDead() const;

    /**
     * @brief Gets the maximum age the entity can live.
     */
    virtual sf::Time getEntityMaxAge() const;

    /**
     * @brief Updates the energy level after being eaten.
     */
    virtual void setEatenEnergy() = 0;

private:
    double energyLevel; ///< Current energy level.
    sf::Time lifetime; ///< Time since creation.
};

