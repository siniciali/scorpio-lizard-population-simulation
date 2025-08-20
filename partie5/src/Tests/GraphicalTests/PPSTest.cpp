/*
 * POOSV 2025
 * Marco Antognini & Jamila Sam
 * STEP : FINAL
 */

#include "PPSTest.hpp"
#include <Animal/Lizard.hpp>
#include <Animal/Scorpion.hpp>
#include <Environment/Cactus.hpp>
#include <Environment/CloudGenerator.hpp>

IMPLEMENT_MAIN(PPSTest)

void PPSTest::onRun()
{
    // Setup stats
    Application::onRun();
    setStats(true);
    resetStats();
}
void PPSTest::onEvent(sf::Event event, sf::RenderWindow& window)
{
    Application::onEvent(event, window);
    onEventPPS(event, window);

}

void PPSTest::onUpdate(sf::Time dt)
{
    Application::onUpdate(dt);
}

void PPSTest::onSimulationStart()
{
    Application::onSimulationStart();
    setSimulationMode(SimulationMode::PPS);

    getAppEnv().addGenerator(new CloudGenerator());


}

void PPSTest::onEventPPS(sf::Event event, sf::RenderWindow&)
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



void PPSTest::resetStats()
{
    Application::resetStats();
    addGraph(s::GENERAL, { s::SCORPIONS, s::LIZARDS, s::CACTUSES,}, 0, 200);
    focusOnStat(s::GENERAL);
}
std::string PPSTest::getHelpTextFile() const
{
    return RES_LOCATION + "help_pps.txt";
}

std::string PPSTest::getWindowTitle() const
{
    return getAppConfig().window_title  + ": PPSTest";
}
