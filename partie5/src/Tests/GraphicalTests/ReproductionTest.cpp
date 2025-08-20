/*
 * POOSV 2025
 * STEP : FINAL
 */

#include "ReproductionTest.hpp"
#include <Animal/Lizard.hpp>
#include <Animal/Scorpion.hpp>
#include <Environment/Cactus.hpp>

IMPLEMENT_MAIN(ReproductionTest)

void ReproductionTest::onRun()
{
    // Setup stats
    Application::onRun();
    setStats(true);
    resetStats();
}

void ReproductionTest::onSimulationStart()
{
    Application::onSimulationStart();
    setSimulationMode(SimulationMode::TEST);

}

std::string ReproductionTest::getHelpTextFile() const
{
    return RES_LOCATION + "help_reproduction.txt";
}

std::string ReproductionTest::getWindowTitle() const
{
    return getAppConfig().window_title  + ":    ReproductionTest ";
}


Animal* create_animal(const Vec2d& position, char type, bool female)
{
    Animal* animal(nullptr);

    switch (type) {
    case 'S' :
        animal = new Scorpion(position, getAppConfig().scorpion_energy_min_mating_male*2, female);
        break;
    case 'L' :
        animal = new Lizard(position, getAppConfig().scorpion_energy_min_mating_female*2, female);
        break;
    default:
        animal = nullptr;
    }
    return animal;
}


void ReproductionTest::onEvent(sf::Event event, sf::RenderWindow&)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::S:
            if(event.key.control) {
                Animal* male = create_animal(getCursorPositionInView(), 'S', false);
                if (male != nullptr)
                    getAppEnv().addEntity(male);
            }

            else {
                Animal* female = create_animal(getCursorPositionInView(), 'S', true);
                if (female != nullptr)
                    getAppEnv().addEntity(female);
            }

            break;
        case sf::Keyboard::L:
            if(event.key.control) {
                Animal* male= create_animal(getCursorPositionInView(), 'L', false);
                if (male != nullptr)
                    getAppEnv().addEntity(male);
            }

            else {
                Animal* female = create_animal(getCursorPositionInView(), 'L', true);
                if (female != nullptr)
                    getAppEnv().addEntity(female);
            }

            break;
        case sf::Keyboard::G:
            getAppEnv().addEntity(new Cactus(getCursorPositionInView()));
            break;

        default:
            break;
        }

    }

}
void ReproductionTest::resetStats()
{
    Application::resetStats();
    addGraph(s::GENERAL, { s::SCORPIONS, s::LIZARDS, s::CACTUSES,}, 0, 200);
    focusOnStat(s::GENERAL);
}
