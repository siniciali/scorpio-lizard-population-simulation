/*
 * POOSV 2025
 * Marco Antognini & Jamila Sam
 * Step : 3
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
    std::string getHelpTextFile() const override;
    std::string getWindowTitle() const override;
};

