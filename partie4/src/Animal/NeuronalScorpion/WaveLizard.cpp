#include "../Animal/NeuronalScorpion/WaveLizard.hpp"
#include "../Environment/Environment.hpp"
#include "../Environment/Wave.hpp"
#include "../Application.hpp"

void WaveLizard::update(sf::Time dt)
{
    this->Lizard::update(dt);
    wave_counter += dt;
    if((wave_counter).asSeconds()>=1/getAppConfig().wave_lizard_frequency) {

        getAppEnv().addWave(new Wave(getPosition(),
                                     getAppConfig().wave_default_energy,
                                     getAppConfig().wave_default_radius,
                                     getAppConfig().wave_default_mu,
                                     getAppConfig().wave_default_speed));

        wave_counter = sf::Time::Zero;

    }
}

void WaveLizard::draw(sf::RenderTarget& targetWindow) const
{
    this->Lizard::draw(targetWindow);
}

WaveLizard::WaveLizard(const Vec2d& initialPosition, double energyLvl, bool isFemale)
    : Lizard(initialPosition, energyLvl, isFemale), wave_counter(sf::Time::Zero)
{}

WaveLizard::WaveLizard(const Vec2d& initialPosition)
    : Lizard(initialPosition), wave_counter(sf::Time::Zero)
{}

WaveLizard::~WaveLizard() {}
