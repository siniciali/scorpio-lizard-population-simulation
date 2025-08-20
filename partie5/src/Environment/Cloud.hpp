#pragma once

#include "../Obstacle/Collider.hpp"

/**
 * @brief Represents a cloud entity in the environment.
 *
 * The Cloud class models a cloud that can evaporate over time
 * depending on environmental temperature and its size.
 */
class Cloud : public Collider
{
public:
    /**
     * @brief Constructs a cloud at a given position and radius.
     * @param position Center position of the cloud.
     * @param radius Initial radius of the cloud.
     */
    Cloud(const Vec2d& position, double radius);

    /**
     * @brief Destructor for the Cloud class.
     */
    ~Cloud() override;

    /**
     * @brief Draws the cloud on the render target if not evaporated.
     * @param targetWindow The window to draw the cloud on.
     */
    void draw(sf::RenderTarget& targetWindow) const override final;

    /**
     * @brief Updates the cloud's state based on environmental conditions.
     * @param dt Time elapsed since the last update.
     */
    void update(sf::Time dt) override final;

    /**
     * @brief Checks if the cloud has evaporated.
     * @return True if the cloud is evaporated.
     */
    bool getEvaporationState() const;

private:
    bool isEvaporated; ///< Whether the cloud has evaporated.
};
