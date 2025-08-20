/*
 * POOSV 2025
 * Marco Antognini & Jamila Sam
 * STEP : FINAL
 */

#pragma once

#include <Application.hpp>

/*!
 * Test the reproduction.
 *
 * Run it with the correct cfg (res/reprod.json) :
 */
class ReproductionTest : public Application
{
public:
    ReproductionTest(int argc, char const** argv)
        :Application(argc, argv)
    {}
    virtual void onEvent(sf::Event event, sf::RenderWindow& window) override final;
    virtual void onSimulationStart() override final;
    virtual void onRun() override final;
    virtual void resetStats() override final;
    std::string getHelpTextFile() const override;
    std::string getWindowTitle() const override;
};

