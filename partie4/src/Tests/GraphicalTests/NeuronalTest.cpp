/*
 * POOSV 2025
 * Marco Antognini & Jamila Sam
 */

#include "NeuronalTest.hpp"
#include <Utility/Utility.hpp>
#include <Config.hpp>
#include <Environment/Wave.hpp>
#include <Obstacle/Rock.hpp>
#include <Animal/NeuronalScorpion/NeuronalScorpion.hpp>

IMPLEMENT_MAIN(NeuronalTest)


void NeuronalTest::onEvent(sf::Event event, sf::RenderWindow&)
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

    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        case sf::Keyboard::R: {
            getAppEnv().clean();
            double position(getAppConfig().simulation_world_size / 2);
            getAppEnv().addEntity(new NeuronalScorpion({position, position}));
        }

        break;
        default:
            break;
        }
    }
}


void NeuronalTest::onSimulationStart()
{
    Application::onSimulationStart();
    setSimulationMode(SimulationMode::NEURONAL);
    double position(getAppConfig().simulation_world_size / 2);
    getAppEnv().addEntity(new NeuronalScorpion({position, position}));
}

void NeuronalTest::newObstacle(Vec2d const& cursor)
{

    Obstacle* obstacle = new Rock(cursor);
    getEnv().addObstacle(obstacle);
}

void NeuronalTest::newWave(Vec2d const& cursor)
{
    Wave* wave = new Wave(cursor,
                          getAppConfig().wave_default_energy,
                          getAppConfig().wave_default_radius,
                          getAppConfig().wave_default_mu,
                          getAppConfig().wave_default_speed);
    getEnv().addWave(wave);
}

std::string NeuronalTest::getHelpTextFile() const
{
    return RES_LOCATION + "help_neuronal.txt";
}

std::string NeuronalTest::getWindowTitle() const
{
    return getAppConfig().window_title  + "Env:   NeuronalTest";
}
