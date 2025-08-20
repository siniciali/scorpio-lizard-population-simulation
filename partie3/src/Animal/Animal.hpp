#pragma once
#include "../Obstacle/Collider.hpp"
#include <SFML/Graphics.hpp>
#include "../Utility/Vec2d.hpp"
#include "../Animal/ChasingAutomaton.hpp"
#include "../Environment/OrganicEntity.hpp"
#include "list"

enum currentState {

    FOOD_IN_SIGHT, // nourriture en vue
    FEEDING,       // en train de manger (là en principe il arrête de se déplacer)
    RUNNING_AWAY,  // en fuite
    MATE_IN_SIGHT, // partenaire en vue
    MATING,        // vie privée (rencontre avec un partenaire!)
    GIVING_BIRTH,  // donne naissance
    WANDERING,     // déambule

};

class Animal : public OrganicEntity
{

public:

    Animal(const Vec2d& position, double size, double energyLvl, bool isfemale);

    ~Animal() override;

    void setTargetPosition (const Vec2d& newposition);
    void setPredatorsPositions (const std::list<Vec2d>& newpositions);

    void setDecelerationMode(DecelerationMode mode);

    void update(sf::Time dt) override;

    void draw(sf::RenderTarget& targetWindow) const override;

    DrawingPriority getDepth() const override;

    virtual double getViewRange() const = 0;

    virtual double getViewDistance() const = 0;

    bool isTargetInSight(const Vec2d& wantedTargetPosition) const;

    virtual double getRandomWalkRadius() const = 0;

    virtual double getRandomWalkDistance() const = 0;

    virtual double getRandomWalkJitter() const = 0;

    Vec2d convertToGlobalCoord(const Vec2d& local)const;

    void randomWalk(double elapsedTime);

    bool getIfIsFemale() const;

    void updateState(sf::Time dt);

    double getMaxSpeed() const;

    void analyzeEnvironment(std::list <OrganicEntity*> entitiesInSight) ;

    void updateEnergy(double elapsed_time);

    bool getIfPregnant() const;

    bool getIfGestating() const;

    virtual double getGestatingTime() const = 0;

    int getNumberBabies() const;

    bool getIfIsDelivering() const;



protected:

    double getRotation() const;

    void setRotation(const double& angle);

    void setDirection(const Vec2d& dir);

    void setNumberBabies(int nbBabies);

    void setPregnancy(bool pregnancy);

    void setGestatingCounter(sf::Time counter);


    //void setIfIsMating(bool mating);

    //void setMatingCounter(sf::Time dt);

    //void setCurrentSate(currentState current_state);

private:

    double speed;

    Vec2d targetPosition;
    std::list<Vec2d> predators_positions;

    Vec2d direction;

    Vec2d current_target;

    DecelerationMode currentDeceleration = Medium;

    double getDeceleration(const DecelerationMode& mode) const;

    Vec2d getAttractionForce(const Vec2d& chosenTarget) const;
    Vec2d getRepulsionForce(const std::list<Vec2d>& predators) const;

    virtual double getStandardMaxSpeed()const = 0;

    virtual double getEnergyLossFactor()const = 0;
    virtual double getInitialEnergy() const = 0;

    virtual double getMass() const = 0;

    Vec2d getSpeedVector () const;

    void debuggingDisplay(sf::RenderTarget& targetWindow) const;

    double viewRange;
    double viewDistance;

    void drawVision(sf::RenderTarget& targetWindow)const;

    Vec2d getClosestTarget(const std::list<Vec2d>& targetsInSight)const;

    OrganicEntity* getClosestEntity(const std::list <OrganicEntity*>& entitiesInSight) const;

    currentState current_state;

    std::list<OrganicEntity*> foodInSight(const std::list<OrganicEntity*> entitiesInSight) const;

    std::list<OrganicEntity*> mateInSight(const std::list<OrganicEntity*> entitiesInSight) const;

    std::list<OrganicEntity*> predatorsInSight(const std::list<OrganicEntity*> entitiesInSight) const;



    bool isFemale;

    bool isFeeding;

    bool isMating;

    bool isPregnant;

    bool isGestating;

    bool isDelivering;

    sf::Time feeding_counter;

    sf::Time mating_counter;

    sf::Time gestating_counter;

    sf::Time delivering_counter;

    std::list<OrganicEntity*> food_in_sight;

    std::list<OrganicEntity*> mate_in_sight;

    std::list<OrganicEntity*> predators_in_sight;

    void targetInSightBehaviour(double elapsedTime);

    void predatorInSightBehaviour(double elapsedTime);

    void feedingBehaviour(sf::Time dt);

    void matingBehaviour(sf::Time dt);

    void deliveringBehaviour(sf::Time dt);

    virtual void giving_birth() = 0;

    int nb_babies;



};
