#pragma once

#include "../Animal/Animal.hpp"

/**
 * @brief Represents a Scorpion entity with specific biological behaviors.
 *
 * The Scorpion class extends the Animal base class and defines species-specific
 * attributes such as movement, reproduction, energy management, and interactions
 * with other entities in the simulation.
 */
class Scorpion : public Animal
{
public:
    /**
     * @brief Constructs a Scorpion with specified energy and gender.
     * @param initialPosition Initial position in the environment.
     * @param energyLvl Initial energy level.
     * @param isFemale True if the scorpion is female.
     */
    Scorpion(const Vec2d& initialPosition, double energyLvl, bool isFemale);

    /**
     * @brief Constructs a Scorpion with default energy and random gender.
     * @param initialPosition Initial position in the environment.
     */
    Scorpion(const Vec2d& initialPosition);

    /**
     * @brief Destructor for Scorpion.
     */
    ~Scorpion() override;

    /**
    * @brief Determines if the scorpion can eat a given organic entity.
    *
    * Uses double dispatch to check species-specific edibility.
    * @param entity Pointer to the other organic entity.
    * @return True if the entity is edible, false otherwise.
    */
    bool eatable(OrganicEntity const* entity) const override final;

    /**
    * @brief Determines if the scorpion can mate with another organic entity.
    *
    * Uses double dispatch to check compatibility and reproduction conditions.
    * @param entity Pointer to the other organic entity.
    * @return True if mating is possible.
    */
    bool matable(OrganicEntity const* entity) const override final;

    /**
    * @brief Handles interaction with another organic entity.
    *
    * Uses double dispatch to trigger species-specific interaction logic.
    * @param entity Pointer to the other organic entity.
    */
    void meet(OrganicEntity* entity) override final;

    /**
    * @brief Gets the energy loss factor for the scorpion.
    *
    * This factor determines how much energy is lost during movement or other actions.
    * @return The energy loss factor.
    */
    double getEnergyLostFactor() const override final;

    /**
    * @brief Gets the initial energy level of the scorpion.
    *
    * This value is used when a scorpion is created with default energy.
    * @return The initial energy value.
    */
    double getInitialEnergy() const override final;

    /**
    * @brief Gets the maximum age the scorpion can live.
    *
    * Once this age is exceeded, the scorpion is considered too old and dies.
    * @return The maximum lifespan as a time duration.
    */
    sf::Time getEntityMaxAge() const override final;

    /**
    * @brief Handles energy behavior when the scorpion is eaten.
    *
    * This method is intentionally left empty since scorpions cannot be eaten.
    */
    void setEatenEnergy() override final;


    /**
    * @brief Gets the duration of the gestation period for a female scorpion.
    * @return The gestation time in seconds.
    */
    double getGestatingTime() const override final;

    /**
    * @brief Handles the birth of a new scorpion.
    *
    * A new scorpion is added to the environment at the parent's position.
    */
    void giving_birth() override final;

    //  === Getters ===

    /**
    * @see The role of these getters is described in OrganicEntity
    */
    double getStandardMaxSpeed() const override final;
    double getMass() const override final;
    double getViewRange() const override final;
    double getViewDistance() const override final;
    double getRandomWalkRadius() const override final;
    double getRandomWalkDistance() const override final;
    double getRandomWalkJitter() const override final;
    std::string getTextureName() const override final;

    /**
    * @brief Increments the scoorpion Counter in the environment.
    */
    void incrementCounter() const override;

private:

    double gestating_time; ///< Duration of gestation for female scorpions.

    /**
    * @brief Checks if the scorpion is eligible for reproduction.
    *
    * The conditions depend on gender, age, energy level, and gestation status.
    * @return True if the scorpion can reproduce.
    */
    bool getIfCanReproduce() const override final;

    // === Double Dispatch Helpers ===

    /**
    * @brief Determines if a scorpion can be eaten by another scorpion.
    *
    * Scorpions are not cannibalistic in this simulation.
    * @param scorpion Pointer to the other scorpion.
    * @return Always returns false.
    */
    bool eatableDispatch(const Scorpion* scorpion) const override final;

    /**
    * @brief Determines if a scorpion can be eaten by a lizard.
    *
    * Scorpions are not prey for lizards in this simulation.
    * @param lizard Pointer to the lizard.
    * @return Always returns false.
    */
    bool eatableDispatch(const Lizard* lizard) const override final;

    /**
    * @brief Determines if a scorpion can be eaten by a cactus.
    *
    * Cacti do not consume other entities.
    * @param food Pointer to the cactus.
    * @return Always returns false.
    */
    bool eatableDispatch(const Cactus* food) const override final;


    /**
    * @brief Determines if this scorpion can mate with another scorpion.
    *
    * Mating is possible if genders differ, both are mature, and both can reproduce.
    * @param scorpion Pointer to the other scorpion.
    * @return True if mating conditions are met.
    */
    bool matableDispatch(Scorpion const* scorpion) const override final;

    /**
    * @brief Determines if this scorpion can mate with a lizard.
    *
    * Cross-species mating is not allowed.
    * @param lizard Pointer to the lizard.
    * @return Always returns false.
    */
    bool matableDispatch(Lizard const* lizard) const override final;

    /**
    * @brief Determines if this scorpion can mate with a cactus.
    *
    * Cross-species mating is not allowed.
    * @param food Pointer to the cactus.
    * @return Always returns false.
    */
    bool matableDispatch(Cactus const* food) const override final;

    /**
    * @brief Handles interaction between this scorpion and a lizard.
    *
    * No specific interaction is defined between scorpions and lizards.
    * @param lizard Pointer to the lizard.
    */
    void meetDispatch(Lizard* lizard) override final;

    /**
    * @brief Handles interaction between two scorpions.
    *
    * If both are compatible for mating, reproduction is initiated.
    * @param scorpion Pointer to the other scorpion.
    */
    void meetDispatch(Scorpion* scorpion) override final;

    /**
    * @brief Handles interaction between this scorpion and a cactus.
    *
    * No specific interaction is defined between scorpions and cacti.
    * @param cactus Pointer to the cactus.
    */
    void meetDispatch(Cactus* cactus) override final;

};
