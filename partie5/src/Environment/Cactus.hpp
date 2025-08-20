#pragma once

#include "../Environment/OrganicEntity.hpp"

/**
 * @brief Represents a cactus in the simulation.
 *
 * Cacti are stationary organic entities that grow when the soil is humid,
 * serve as food for lizards, but cannot reproduce or interact with others meaningfully.
 */
class Cactus : public OrganicEntity
{
public:

    /**
     * @brief Constructs a cactus at a given position with default energy.
     * @param position The position where the cactus is placed in the environment.
     */
    Cactus(const Vec2d& position);

    /**
     * @brief Destructor.
     */
    ~Cactus() override;


    // === Overridden simulation interface ===

    /**
     * @brief Updates the cactus' growth if humidity is present.
     */
    void update(sf::Time dt) override;
    /**
     * @brief Renders the cactus sprite and debug radius.
     */
    void draw(sf::RenderTarget& targetWindow) const override;

    /**
     * @brief Returns the texture name associated with the cactus.
     * @return A string representing the cactus texture identifier.
     */
    std::string getTextureName() const override final;
    /**
     * @brief Returns the rendering depth priority of the cactus.
     * @return The drawing priority specific to cactus entities.
     */
    DrawingPriority getDepth() const override final;

    // === Double dispatch for interaction semantics ===

    /**
     * @brief Determines whether the cactus is eatable by the given entity.
     * @param entity Pointer to the other organic entity.
     * @return True if the entity can eat the cactus, false otherwise.
     */
    bool eatable(OrganicEntity const* entity) const override;
    /**
     * @brief Determines whether the cactus can mate with the given entity.
     * @param other Pointer to the potential mating partner.
     * @return Always false — cacti cannot reproduce.
     */
    bool matable(OrganicEntity const* other) const override;
    /**
     * @brief Handles the interaction logic when another entity meets the cactus.
     * @param other Pointer to the interacting organic entity.
     */
    void meet(OrganicEntity* other) override;

    /**
     * @brief Reduces cactus energy after being eaten.
     */
    void setEatenEnergy() override;

    /**
     * @brief Increments the number of cacti in the environment
     */
    void incrementCounter() const override;

private:
    // === Double dispatch implementations ===
    bool eatableDispatch(const Scorpion* scorpion) const override;
    bool eatableDispatch(const Lizard* lizard) const override;
    bool eatableDispatch(const Cactus* food) const override;

    bool matableDispatch(Scorpion const* scorpion) const override;
    bool matableDispatch(Lizard const* lizard) const override;
    bool matableDispatch(Cactus const* food) const override;

    void meetDispatch(Lizard* lizard) override;
    void meetDispatch(Scorpion* scorpion) override;
    void meetDispatch(Cactus* cactus) override;

    /**
     * @brief Indicates if the cactus is capable of reproduction.
     * @return Always false — cacti do not reproduce in this simulation.
     */
    bool getIfCanReproduce() const override;

};


