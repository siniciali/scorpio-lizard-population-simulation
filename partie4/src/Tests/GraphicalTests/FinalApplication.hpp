/*
 *  POOSV 2025
 * Marco Antognini & Jamila Sam
 * STEP 3 + 4
 */

#pragma once

#include <Application.hpp>

class FinalApplication : public Application
{
public:
    FinalApplication(int argc, char const** argv)
        : Application(argc, argv)
    {}


    virtual void onEvent(sf::Event event, sf::RenderWindow& window) override final;
    virtual void onUpdate(sf::Time dt) override final;
    virtual void onRun() override final;
    std::string getHelpTextFile() const override;
    std::string getWindowTitle() const override;

private:
    void onEventPPS(sf::Event event, sf::RenderWindow& window);
    void onUpdatePPS(sf::Time dt);

    void onSimulationStart() override;

    void onEventNeuronal(sf::Event event, sf::RenderWindow& window);
    void onUpdateNeuronal(sf::Time dt);
};


