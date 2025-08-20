/*
 *  POOSV 2025
 * Marco Antognini & Jamila Sam
 * Step : 3
 */

#include "FinalApplication.hpp"
#include <Animal/Lizard.hpp>
#include <Animal/Scorpion.hpp>
#include <Environment/Cactus.hpp>
#include <Environment/CloudGenerator.hpp>
#include <Environment/Wave.hpp>

IMPLEMENT_MAIN(FinalApplication)

void FinalApplication::onRun()
{
    // Setup stats
    Application::onRun();
}
void FinalApplication::onEvent(sf::Event event, sf::RenderWindow& window)
{
    onEventPPS(event, window);
}

void FinalApplication::onUpdate(sf::Time dt)
{
    Application::onUpdate(dt);
    onUpdatePPS(dt);
}

void FinalApplication::onSimulationStart()
{
    Application::onSimulationStart();
    setSimulationMode(SimulationMode::PPS);
    getAppEnv().addGenerator(new CloudGenerator());
}

void FinalApplication::onEventPPS(sf::Event event, sf::RenderWindow&)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::S:
            getAppEnv().addEntity(new Scorpion(getCursorPositionInView()));
            break;

        case sf::Keyboard::L:
            getAppEnv().addEntity(new Lizard(getCursorPositionInView()));
            break;

        case sf::Keyboard::G:
            getAppEnv().addEntity(new Cactus(getCursorPositionInView()));
            break;

        default:
            break;
        }
    }
}

void FinalApplication::onUpdatePPS(sf::Time)
{
    // Nothing
}



std::string FinalApplication::getHelpTextFile() const
{
    return RES_LOCATION + "help.txt";
}

std::string FinalApplication::getWindowTitle() const
{
    return getAppConfig().window_title  + " (main simulation)";
}
