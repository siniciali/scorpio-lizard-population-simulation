/*
 * POOSV 2025
 * Marco Antognini & Jamila Sam
 */

#pragma once

#include <Application.hpp>
#include <Obstacle/Collider.hpp>

typedef Collider Obstacle;

/*!
 * Test the neuronal scorpion.
 *
 * Generate one wave on left click, or continuous waves when right clic is kept pressed
 */
class NeuronalTest : public Application
{
public:
    NeuronalTest(int argc, char const** argv)
        : Application(argc, argv)
    {
    }

    virtual void onEvent(sf::Event event, sf::RenderWindow& window) final override;
    virtual void onSimulationStart() override final;

    std::string getHelpTextFile() const override;
    std::string getWindowTitle() const override;
private:
    void newWave(Vec2d const& cursor);
    void newObstacle(Vec2d const& cursor);
};


