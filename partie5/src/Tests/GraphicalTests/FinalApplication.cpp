/*
 *  POOSV 2025
 * Marco Antognini & Jamila Sam
 * STEP : FINAL
 */

#include "FinalApplication.hpp"
#include "../../Animal/Lizard.hpp"
#include "../../Animal/Scorpion.hpp"
#include "../../Animal/NeuronalScorpion/NeuronalScorpion.hpp"
#include "../../Animal/NeuronalScorpion/WaveLizard.hpp"
#include "../../Environment/Cactus.hpp"
#include "../../Environment/CloudGenerator.hpp"
#include "../../Environment/Wave.hpp"
#include "../../Obstacle/Rock.hpp"

IMPLEMENT_MAIN(FinalApplication)

void FinalApplication::onRun()
{
    // Setup stats
    Application::onRun();
    setStats(true);
    resetStats();
}
void FinalApplication::onEvent(sf::Event event, sf::RenderWindow& window)
{
    bool const toggle = event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Tab;

    if (toggle) {
        switch (getSimulationMode()) {
        case SimulationMode::PPS:
            setSimulationMode(SimulationMode::NEURONAL);
            break;

        case SimulationMode::NEURONAL:
            setSimulationMode(SimulationMode::PPS);
            break;
        case SimulationMode::TEST :
            /*nothing to do */
            break;
        }
        initHelpBox();
        toggleStats();
    }

    else {
        switch (getSimulationMode()) {
        case SimulationMode::PPS:
            onEventPPS(event, window);
            break;

        case SimulationMode::NEURONAL:
            onEventNeuronal(event, window);
            break;
        case SimulationMode::TEST :
            /*nothing to do */
            break;
        }
    }

}

void FinalApplication::onUpdate(sf::Time dt)
{
    Application::onUpdate(dt);
    switch (getSimulationMode()) {
    case SimulationMode::PPS:
        onUpdatePPS(dt);
        break;

    case SimulationMode::NEURONAL:
        onUpdateNeuronal(dt);
        break;
    case SimulationMode::TEST :
        /*nothing to do */
        break;
    }
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


void FinalApplication::onEventNeuronal(sf::Event event, sf::RenderWindow&)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::W:
            getAppEnv().addEntity(new WaveLizard(getCursorPositionInView()));
            break;

        case sf::Keyboard::N:
            getAppEnv().addEntity(new NeuronalScorpion(getCursorPositionInView()));
            break;

        // WE ADDED KEYBOARD COMMAND "O" TO SPAWN ROCKS IN THE FINAL SIMULATION
        case sf::Keyboard::O:
            getAppEnv().addObstacle(new Rock(getCursorPositionInView()));
            break;

        //WE ADDED KEYBORD COMMAND "G" TO SPAWN CACTI IN THE NEURONAL (FINAL) SIMULATION
        case sf::Keyboard::G:
            getAppEnv().addEntity(new Cactus(getCursorPositionInView()));
            break;

        default:
            break;
        }
    }
}

void FinalApplication::onUpdateNeuronal(sf::Time)
{
    // Nothing
}


void FinalApplication::resetStats()
{
    Application::resetStats();
    addGraph(s::GENERAL, { s::SCORPIONS, s::LIZARDS, s::CACTUSES,}, 0, 100);
    addGraph(s::WAVES, { s::WAVES, s::NEURONALSCORPION, s::WAVELIZARD, s::CACTUSES}, 0, 100);
    focusOnStat(s::GENERAL);
}

std::string FinalApplication::getHelpTextFile() const
{
    if (getSimulationMode() == SimulationMode::PPS)
        return RES_LOCATION + "help.txt";
    return RES_LOCATION + "help_neuronal.txt";
}

std::string FinalApplication::getWindowTitle() const
{
    return getAppConfig().window_title  + " (main simulation)";
}
