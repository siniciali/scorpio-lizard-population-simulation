/*
* prjsv 2019
* 2016-19
* Marco Antognini & Jamila Sam
*/

#include <Application.hpp>
#include <Animal/Lizard.hpp>
#include <Animal/Scorpion.hpp>
#include <Environment/OrganicEntity.hpp>
#include <Environment/Cactus.hpp>
#include <Config.hpp>
#include <catch.hpp>
#include <iostream>

SCENARIO("Gerbils' reproduction", "[Gerbil]")
{

    OrganicEntity* male_lizard1(new Lizard({0,0}, 0, false));
    OrganicEntity* male_lizard2(new Lizard({0,0}, getAppConfig().lizard_energy_min_mating_male, false));
    OrganicEntity* female_lizard1(new Lizard({0,0}, 0, true));
    OrganicEntity* female_lizard2(new Lizard({0,0}, getAppConfig().lizard_energy_min_mating_female, true));
    OrganicEntity* female_scorpion(new Scorpion({0,0}, getAppConfig().scorpion_energy_min_mating_female, true));
    OrganicEntity* male_scorpion(new Scorpion({0,0}, getAppConfig().scorpion_energy_min_mating_male, false));
    OrganicEntity*food(new Cactus({0,0}));

    // make some lizards sufficiently mature
    auto age(sf::seconds(getAppConfig().lizard_min_age_mating));
    male_lizard2->OrganicEntity::update(age);
    female_lizard2->OrganicEntity::update(age);

    GIVEN("two lizards of same gender") {
        THEN("no mating") {
            CHECK_FALSE(male_lizard1->matable(male_lizard1));
            CHECK_FALSE(male_lizard1->matable(male_lizard2));
            CHECK_FALSE(male_lizard2->matable(male_lizard1));
            CHECK_FALSE(female_lizard1->matable(female_lizard1));
            CHECK_FALSE(female_lizard1->matable(female_lizard2));
            CHECK_FALSE(female_lizard2->matable(female_lizard1));
        }
    }
    GIVEN("two lizards of different genders, but too weak") {
        THEN("no mating") {
            CHECK_FALSE(male_lizard1->matable(female_lizard1));
            CHECK_FALSE((male_lizard2->matable(female_lizard1)
                         and female_lizard1->matable(male_lizard2)));
            CHECK_FALSE((female_lizard2->matable(male_lizard1)
                         and male_lizard1->matable(female_lizard2)));
        }
    }

    GIVEN("a lizard and a scorpion") {

        THEN("no mating") {
            CHECK_FALSE(male_lizard2->matable(female_scorpion));
            CHECK_FALSE(female_scorpion->matable(male_lizard2));
            CHECK_FALSE(female_lizard2->matable(male_scorpion));
            CHECK_FALSE(male_scorpion->matable(female_lizard2));
        }
    }

    GIVEN("a lizard and a food") {

        THEN("no mating") {
            CHECK_FALSE(male_lizard2->matable(food));
            CHECK_FALSE(female_lizard2->matable(food));
            CHECK_FALSE(food->matable(female_lizard2));
            CHECK_FALSE(food->matable(male_lizard2));
        }
    }

    GIVEN("two sufficiently old lizards of different genders and enough energy") {

        THEN("reproduction is possible") {
            CHECK(male_lizard2->matable(female_lizard2));
            CHECK(female_lizard2->matable(male_lizard2));
        }
    }

    delete male_lizard1;
    delete male_lizard2;
    delete female_lizard1;
    delete female_lizard2;
    delete food;
    delete male_scorpion;
    delete female_scorpion;
}

SCENARIO("Scorpions' reproduction", "[Scorpion]")
{

    OrganicEntity* male_scorpion1(new Scorpion({0,0}, 0, false));
    OrganicEntity* male_scorpion2(new Scorpion({0,0}, getAppConfig().scorpion_energy_min_mating_male, false));
    OrganicEntity* female_scorpion1(new Scorpion({0,0}, 0, true));
    OrganicEntity* female_scorpion2(new Scorpion({0,0}, getAppConfig().scorpion_energy_min_mating_female, true));
    OrganicEntity* female_lizard(new Lizard({0,0}, getAppConfig().lizard_energy_min_mating_female, true));
    OrganicEntity* male_lizard(new Lizard({0,0}, getAppConfig().lizard_energy_min_mating_male, false));
    OrganicEntity*food(new Cactus({0,0}));
    // make some scorpions sufficiently mature
    auto age(sf::seconds(getAppConfig().scorpion_min_age_mating));
    male_scorpion2->OrganicEntity::update(age);
    female_scorpion2->OrganicEntity::update(age);

    GIVEN("two scorpions of same gender") {
        THEN("no mating") {
            CHECK_FALSE(male_scorpion1->matable(male_scorpion1));
            CHECK_FALSE(male_scorpion1->matable(male_scorpion2));
            CHECK_FALSE(male_scorpion2->matable(male_scorpion1));
            CHECK_FALSE(female_scorpion1->matable(female_scorpion1));
            CHECK_FALSE(female_scorpion1->matable(female_scorpion2));
            CHECK_FALSE(female_scorpion2->matable(female_scorpion1));
        }
    }
    GIVEN("two scorpions of different genders, but too weak") {
        THEN("no mating") {
            CHECK_FALSE(male_scorpion1->matable(female_scorpion1));
            CHECK_FALSE((male_scorpion2->matable(female_scorpion1)
                         and female_scorpion1->matable(male_scorpion2)));
            CHECK_FALSE((female_scorpion2->matable(male_scorpion1)
                         and male_scorpion1->matable(female_scorpion2)));
        }
    }

    GIVEN("a scorpion and a lizard") {

        THEN("no mating") {
            CHECK_FALSE(male_scorpion2->matable(female_lizard));
            CHECK_FALSE(female_lizard->matable(male_scorpion2));
            CHECK_FALSE(female_scorpion2->matable(male_lizard));
            CHECK_FALSE(male_lizard->matable(female_scorpion2));
        }
    }

    GIVEN("a scorpion and a food") {

        THEN("no mating") {
            CHECK_FALSE(male_scorpion2->matable(food));
            CHECK_FALSE(female_scorpion2->matable(food));
            CHECK_FALSE(food->matable(female_scorpion2));
            CHECK_FALSE(food->matable(male_scorpion2));
        }
    }

    GIVEN("two scorpions of different genders and enough energy") {

        THEN("reproduction is possible") {
            CHECK(male_scorpion2->matable(female_scorpion2));
            CHECK(female_scorpion2->matable(male_scorpion2));
        }
    }

    delete male_scorpion1;
    delete male_scorpion2;
    delete female_scorpion1;
    delete female_scorpion2;
    delete food;
    delete male_lizard;
    delete female_lizard;
}
