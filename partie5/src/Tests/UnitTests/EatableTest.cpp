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

SCENARIO("Gerbil vs OrganicEntity", "[Gerbil]")
{

    OrganicEntity* lizard1(new Lizard({0,0}));
    OrganicEntity* lizard2(new Lizard({0,0}));
    OrganicEntity* scorpion1(new Scorpion({0,0}));
    OrganicEntity* food1(new Cactus({0,0}));

    GIVEN("a lizard") {
        THEN("no autophagy") {
            CHECK_FALSE(lizard1->eatable(lizard1));
        }
    }
    GIVEN("two lizards") {
        THEN("no cannibalism") {
            CHECK_FALSE(lizard1->eatable(lizard2));
            CHECK_FALSE(lizard2->eatable(lizard1));
        }
    }

    GIVEN("a lizard and a food") {

        THEN("the food is eatable by the lizard") {
            CHECK(lizard1->eatable(food1));
        }
        THEN("the lizard is not eatable by the food") {
            CHECK_FALSE(food1->eatable(lizard1));
        }
    }

    GIVEN("a lizard and a scorpion") {

        THEN("the lizard is eatable by the scorpion") {
            CHECK(scorpion1->eatable(lizard1));
        }
        THEN("the scorpion is not eatable by the lizard") {
            CHECK_FALSE(lizard1->eatable(scorpion1));
        }
    }
    delete lizard1;
    delete lizard2;
    delete scorpion1;
    delete food1;
}

SCENARIO("Food vs OrganicEntity", "[Food]")
{

    OrganicEntity* lizard1(new Lizard({0,0}));
    OrganicEntity* scorpion1(new Scorpion({0,0}));
    OrganicEntity* food1(new Cactus({0,0}));
    OrganicEntity* food2(new Cactus({0,0}));
    GIVEN("a food") {
        THEN("no autophagy") {
            CHECK_FALSE(food1->eatable(food1));
        }
    }
    GIVEN("two foods") {
        THEN("no cannibalism") {
            CHECK_FALSE(food1->eatable(food2));
            CHECK_FALSE(food2->eatable(food1));
        }
    }

    GIVEN("a food and a scorpion") {

        THEN("the food is not eatable by the scorpion") {
            CHECK_FALSE(scorpion1->eatable(food1));
        }
        THEN("the scorpion is not eatable by the food") {
            CHECK_FALSE(food1->eatable(scorpion1));
        }
    }

    GIVEN("a food and a lizard") {

        THEN("the food is eatable by the lizard") {
            CHECK(lizard1->eatable(food1));
        }
        THEN("the lizard is not eatable by the food") {
            CHECK_FALSE(food1->eatable(lizard1));
        }
    }
    delete lizard1;
    delete scorpion1;
    delete food1;
    delete food2;
}

SCENARIO("Scorpion vs OrganicEntity", "[Scorpion]")
{

    OrganicEntity* lizard1(new Lizard({0,0}));
    OrganicEntity* scorpion1(new Scorpion({0,0}));
    OrganicEntity* scorpion2(new Scorpion({0,0}));
    OrganicEntity* food1(new Cactus({0,0}));

    GIVEN("a scorpion") {
        THEN("no autophagy") {
            CHECK_FALSE(scorpion1->eatable(scorpion1));
        }
    }
    GIVEN("two wolves") {
        THEN("no cannibalism") {
            CHECK_FALSE(scorpion1->eatable(scorpion2));
            CHECK_FALSE(scorpion2->eatable(scorpion1));
        }
    }

    GIVEN("a Scorpion and a food") {

        THEN("the food is not eatable by the scorpion") {
            CHECK_FALSE(scorpion1->eatable(food1));
        }
        THEN("the scorpion is not eatable by the food") {
            CHECK_FALSE(food1->eatable(scorpion1));
        }
    }

    GIVEN("a scorpion and a lizard") {

        THEN("the lizard is eatable by the scorpion") {
            CHECK(scorpion1->eatable(lizard1));
        }
        THEN("the scorpion is not eatable by the lizard") {
            CHECK(scorpion1->eatable(lizard1));
        }
    }
    delete lizard1;
    delete scorpion1;
    delete scorpion2;
    delete food1;
}
