/*
 * POOSV 2025
 * Marco Antognini & Jamila Sam
 */

#include "WaveTest.hpp"
#include <Utility/Utility.hpp>
#include <Config.hpp>
#include <Environment/Wave.hpp>
#include <Obstacle/Rock.hpp> // UNCOMMENT WHEN Rock IS CODED

IMPLEMENT_MAIN(WaveTest)


void WaveTest::onEvent(sf::Event event, sf::RenderWindow&)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        switch (event.mouseButton.button) {
        case sf::Mouse::Button::Left:
            newWave(getCursorPositionInView());
            break;

        case sf::Mouse::Button::Right:
            newObstacle(getCursorPositionInView());
            break;

        default:
            break;
        }
    }
}

std::string WaveTest::getHelpTextFile() const
{
    return RES_LOCATION + "help_wave.txt";
}

std::string WaveTest::getWindowTitle() const
{
    return getAppConfig().window_title  + ":    WaveTest ";
}

void WaveTest::newObstacle(Vec2d const& cursor)
{
    // UNCOMMENT WHEN READY TO TEST
    Obstacle* obstacle = new Rock(cursor);
    getEnv().addObstacle(obstacle);

}

void WaveTest::newWave(Vec2d const& cursor)
{
    Wave* wave = new Wave(cursor,
                          getAppConfig().wave_default_energy,
                          getAppConfig().wave_default_radius,
                          getAppConfig().wave_default_mu,
                          getAppConfig().wave_default_speed);
    getEnv().addWave(wave);
}

