#pragma once
#include "../Utility/Utility.hpp"
#include "../Interface/Updatable.hpp"

class CloudGenerator : public Updatable
{
public:

    CloudGenerator ();

    ~CloudGenerator() override;

    void update(sf::Time dt) override;

private:
    sf::Time tcounter;
};

