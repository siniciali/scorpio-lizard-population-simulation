#pragma once

#include "../Animal/Animal.hpp"
#include "../Utility/Vec2d.hpp"


/**
 * @brief Represents a Lizard entity in the simulation.
 *
 * The Lizard class models a lizard with behaviors such as movement,
 * reproduction, perception, and interaction with other entities.
 */
class Lizard : public Animal
{
public:
    /**
     * @brief Constructs a Lizard with a specific position, energy level, and sex.
     * @param initialPosition Initial position of the lizard.
     * @param energyLvl Initial energy level.
     * @param isFemale True if the lizard is female.
     */
    Lizard(const Vec2d& initialPosition, double energyLvl, bool isFemale);

    /**
     * @brief Constructs a Lizard with a specific position and random sex.
     *        Energy is initialized from configuration.
     * @param initialPosition Initial position of the lizard.
     */
    Lizard(const Vec2d& initialPosition);

    /**
     * @brief Destructor for the Lizard class.
     */
    virtual ~Lizard() override;

    // === Getters ===
    double getStandardMaxSpeed() const override final;
    double getMass() const override final;
    double getViewRange() const override final;
    double getViewDistance() const override final;
    double getRandomWalkRadius() const override final;
    double getRandomWalkDistance() const override final;
    double getRandomWalkJitter() const override final;
    std::string getTextureName() const override final;


    /**
    * @brief Increments the lizard Counter in the environment.
    */
    void incrementCounter() const override;

    /**
     * @brief Determines if the lizard can eat the given entity.
     * @param entity Pointer to the entity to check.
     * @return True if the entity is eatable.
     */
    bool eatable(OrganicEntity const* entity) const override;

    /**
     * @brief Determines if the lizard can mate with the given entity.
     * @param entity Pointer to the entity to check.
     * @return True if the entity is matable.
     */
    bool matable(OrganicEntity const* entity) const override;

    /**
     * @brief Handles interaction with another entity.
     * @param entity Pointer to the entity to interact with.
     */
    void meet(OrganicEntity* entity) override;

    /**
    * @brief Gets the maximum age the lizard can live.
    *
    * Once this age is exceeded, the lizard is considered too old and dies.
    * @return The maximum lifespan as a time duration.
    */
    sf::Time getEntityMaxAge() const override;

    /**
    * @brief Gets the energy loss factor for the lizard.
    *
    * This factor determines how much energy is lost during movement or other actions.
    * @return The energy loss factor.
    */
    double getEnergyLostFactor() const override;

    /**
    * @brief Gets the initial energy level of the scorpion.
    *
    * This value is used when a scorpion is created with default energy.
    * @return The initial energy value.
    */
    double getInitialEnergy() const override;

    /**
     * @brief Updates the lizard's state.
     * @param dt Time elapsed since the last update.
     */
    void update(sf::Time dt) override;

    /**
     * @brief Sets the lizard's energy to zero after being eaten.
     */
    void setEatenEnergy() override final;

    /**
     * @brief Gets the gestation time for the lizard.
     * @return Gestation time in seconds.
     */
    double getGestatingTime() const override final;

    /**
     * @brief Handles the birth of a new lizard.
     */
    void giving_birth() override final;



private:


    bool texture_orientation = false; ///< Orientation state for texture switching.
    double gestating_time; ///< Time required for gestation.

    /**
     * @brief Checks if the lizard is eligible for reproduction.
     * @return True if the lizard can reproduce.
     */
    bool getIfCanReproduce() const override final;

    // === Double Dispatch Helpers ===

    /**
     * @brief Determines if the lizard can eat a scorpion.
     * @param scorpion Pointer to the scorpion to check.
     * @return True if the scorpion is eatable.
     */
    bool eatableDispatch(const Scorpion* scorpion) const override final;

    /**
     * @brief Determines if the lizard can eat another lizard.
     * @param lizard Pointer to the lizard to check.
     * @return True if the lizard is eatable.
     */
    bool eatableDispatch(const Lizard* lizard) const override final;

    /**
     * @brief Determines if the lizard can eat a cactus.
     * @param food Pointer to the cactus to check.
     * @return True if the cactus is eatable.
     */
    bool eatableDispatch(const Cactus* food) const override final;

    /**
     * @brief Determines if the lizard can mate with a scorpion.
     * @param scorpion Pointer to the scorpion to check.
     * @return True if the scorpion is matable.
     */
    bool matableDispatch(Scorpion const* scorpion) const override final;

    /**
     * @brief Determines if the lizard can mate with another lizard.
     * @param lizard Pointer to the lizard to check.
     * @return True if the lizard is matable.
     */
    bool matableDispatch(Lizard const* lizard) const override final;

    /**
     * @brief Determines if the lizard can mate with a cactus.
     * @param cactus Pointer to the cactus to check.
     * @return True if the cactus is matable.
     */
    bool matableDispatch(Cactus const* food) const override final;

    /**
     * @brief Handles interaction with another lizard.
     * @param lizard Pointer to the lizard to interact with.
     */
    void meetDispatch(Lizard* lizard) override final;

    /**
     * @brief Handles interaction with a scorpion.
     * @param scorpion Pointer to the scorpion to interact with.
     */
    void meetDispatch(Scorpion* scorpion) override final;

    /**
     * @brief Handles interaction with a cactus.
     * @param cactus Pointer to the cactus to interact with.
     */
    void meetDispatch(Cactus* cactus) override final;

};
