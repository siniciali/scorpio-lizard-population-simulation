/*
 * POOSV 2025
 * Marco Antognini & Jamila Sam
 * Step 3
 */

#pragma once

#include "Application.hpp"

class PPSTest : public Application
{
public:
    PPSTest(int argc, char const** argv)
        : Application(argc, argv)
    {}
    virtual void onEvent(sf::Event event, sf::RenderWindow& window) override final;
    virtual void onUpdate(sf::Time dt) override final;
    std::string getHelpTextFile() const override;
    std::string getWindowTitle() const override;
private:
    void onEventPPS(sf::Event event, sf::RenderWindow& window);
    void onSimulationStart() override;
};


