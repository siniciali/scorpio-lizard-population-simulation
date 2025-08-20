/*
 * POOSV 2025
 * Marco Antognini & Jamila Sam
 */

#pragma once

#include <Application.hpp>
#include <Obstacle/Collider.hpp>

typedef Collider Obstacle;

/*!
 * Test the wave.
 *
 * Generate one wave on left click, or continuous waves when right clic is kept pressed
 */
class WaveTest : public Application
{
public:
    WaveTest(int argc, char const** argv)
        : Application(argc, argv)
    {
    }

    virtual void onEvent(sf::Event event, sf::RenderWindow& window) final override;
    std::string getHelpTextFile() const override;
    std::string getWindowTitle() const override;
private:
    void newWave(Vec2d const& cursor);
    void newObstacle(Vec2d const& cursor);
};



