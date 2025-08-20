#pragma once

#include "../Animal/Lizard.hpp"

/**
 * @brief A specialized Lizard that emits waves periodically.
 *
 * The WaveLizard extends the base Lizard class by emitting wave signals
 * at a configurable frequency, useful for interaction with wave-sensitive entities.
 */
class WaveLizard : public Lizard
{
public:
    /**
     * @brief Constructs a WaveLizard with full parameters.
     * @param initialPosition Starting position of the lizard.
     * @param energyLvl Initial energy level.
     * @param isFemale Gender flag.
     */
    WaveLizard(const Vec2d& initialPosition, double energyLvl, bool isFemale);

    /**
     * @brief Constructs a WaveLizard with default energy and gender.
     * @param initialPosition Starting position of the lizard.
     */
    WaveLizard(const Vec2d& initialPosition);

    /**
     * @brief Destructor for WaveLizard.
     */
    ~WaveLizard() override;

    /**
     * @brief Updates the lizard and emits waves periodically.
     * @param dt Time elapsed since the last update.
     */
    void update(sf::Time dt) override;

    /**
     * @brief Draws the lizard on the render target.
     * @param targetWindow The window to draw on.
     */
    void draw(sf::RenderTarget& targetWindow) const override;

    /**
    * @brief Increments the wave lizard Counter in the environment.
    */
    void incrementCounter() const override final;

private:
    sf::Time wave_counter; ///< Timer to control wave emission frequency.
};
