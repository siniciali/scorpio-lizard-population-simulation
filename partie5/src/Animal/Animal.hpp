#pragma once
#include "../Obstacle/Collider.hpp"
#include "SFML/Graphics.hpp"
#include "../Environment/OrganicEntity.hpp"
#include "list"

/**
 * @brief States describing the behaviour of an animal.
 */
enum currentState {

    FOOD_IN_SIGHT,  ///< Moving toward visible food.
    FEEDING,        ///< Paused while consuming food; no displacement.
    RUNNING_AWAY,   ///< Evading predators.
    MATE_IN_SIGHT,  ///< Moving toward a potential mate.
    MATING,         ///< In-place reproduction ritual.
    GIVING_BIRTH,   ///< Delivering offspring.
    WANDERING       ///< Default random walk when no stimulus is present.
};

/**
 * @brief Base class for all mobile living entities in the simulation.
 *
 * This class handles all shared behaviour logic related to energy management,
 * reproduction, and predator/prey interactions. Subclasses must implement
 * various biological constants and the method to generate offspring.
 */
class Animal : public OrganicEntity
{

public:
    /**
     * @brief Constructs an animal with base radius, energy and sex.
     * @param position Initial position of the animal.
     * @param size Initial radius.
     * @param energyLvl Initial energy level.
     * @param isfemale True if the animal is female, false otherwise.
     */
    Animal(const Vec2d& position, double size, double energyLvl, bool isfemale);
    /**
     * @brief Destructor.
     */
    ~Animal() override;

    /**
     * @brief Main update routine, called every frame.
     */
    void update(sf::Time dt) override;

    /**
     * @brief Draws the animal to the given render target.
     */
    void draw(sf::RenderTarget& targetWindow) const override;

    /**
     * @brief Checks if a target position is within the animal's field of view.
     * @param wantedTargetPosition The position to check.
     * @return True if the position is in sight, false otherwise.
     * @note Is put in public because Environment uses it
     */
    bool isTargetInSight(const Vec2d& wantedTargetPosition) const;


protected:

    /**
     * @brief Returns the sex of the animal.
     */
    bool getIfIsFemale() const;

    /**
     * @brief Classifies nearby entities into categories (food, mates, predators).
     * @param entitiesInSight List of entities perceived by the animal.
     */
    void analyzeEnvironment(const std::list <OrganicEntity*>& entitiesInSight) ;

    /**
     * @param local A vector in local coordinates (relative to the animal).
     * @return The corresponding global coordinates.
     */
    Vec2d convertToGlobalCoord(const Vec2d& local)const;

    /**
     * @brief Moves randomly using jittered circular target.
     */
    void randomWalk(double elapsedTime);

    /**
     * @brief Returns the current angle of displacement.
     */
    double getRotation() const;

    /**
     * @brief Sets the current angle of displacement.
     */
    void setRotation(const double& angle);

    /**
     * @brief Sets the current direction.
     */
    void setDirection(const Vec2d& dir);

    /**
     * @brief Sets the number of babies.
     */
    void setNumberBabies(int nbBabies);

    /**
     * @brief Sets pregnancy state.
     */
    void setPregnancy(bool pregnancy);

    /**
     * @brief Sets gestating counter to the wanted value.
     */
    void setGestatingCounter(sf::Time counter);

    /**
     * @brief Moves toward the current target (food or mate).
     */
    void targetInSightBehaviour(double elapsedTime);

    /**
     * @brief Returns if animal is pregnant.
     */
    bool getIfPregnant() const;

    /**
     * @brief Returns if animal is gestating.
     */
    bool getIfGestating() const;

    /**
     * @param entitiesInSight List of visible organic entities.
     * @return Pointer to the closest entity, or nullptr if none.
     */
    OrganicEntity* getClosestEntity(const std::list <OrganicEntity*>& entitiesInSight) const;

    /**
     * @brief Returns the number of babies.
     */
    int getNumberBabies() const;

    /**
     * @brief Returns if animal is in delivering state.
     */
    bool getIfIsDelivering() const;

    /**
     * @brief Returns a list on the foods that are in the animal's sight.
     */
    std::list <OrganicEntity*> getFoodInSight() const;

    /**
     * @param chosenTarget Position to steer toward.
     * @return Force vector directing the animal toward the target.
     */
    Vec2d getAttractionForce(const Vec2d& chosenTarget) const;

    /**
     * @brief Returns current speed vector (direction * speed).
     */
    Vec2d getSpeedVector () const;

    /**
     * @brief Draws perception cone.
     */
    void drawVision(sf::RenderTarget& targetWindow)const;

    /**
     * @brief Draws hitbox outline.
     */
    void drawHitbox(sf::RenderTarget& targetWindow)const;

    /**
     * @brief Sets new target position (used in steering).
     */
    void setTargetPosition (const Vec2d& newPosition);


private:

    double speed; ///< Scalar speed value.
    Vec2d targetPosition; ///< Current navigation goal.
    std::list<Vec2d> predators_positions; ///< Locations of visible threats.
    Vec2d direction; ///< Normalized heading direction.
    Vec2d current_target; ///< Internal wandering target.

    DecelerationMode currentDeceleration = Medium; ///< Deceleration level set to medium by default.

    /**
     * @param mode Selected deceleration strategy (Weak, Medium, Strong).
     * @return Numerical deceleration factor.
     */
    double getDeceleration(DecelerationMode mode) const;

    /**
     * @param predators List of predator positions.
     * @return Total repulsive force vector from all predators.
     */
    Vec2d getRepulsionForce(const std::list<Vec2d>& predators) const;

    /**
     * @brief Pure virtual method that returns the max speed in a polymorphic way.
     */
    virtual double getStandardMaxSpeed()const = 0;

    /**
     * @brief Pure virtual method that returns energy loss factor in a polymorphic way.
     */
    virtual double getEnergyLostFactor()const = 0;

    /**
     * @brief Pure virtual method that returns the initial energy of the animal in a polymorphic way.
     */
    virtual double getInitialEnergy() const = 0;

    /**
     * @brief Pure virtual method that returns the mass of the animal in a polymorphic way.
     */
    virtual double getMass() const = 0;

    /**
     * @brief Draw the debugging display.
     */
    virtual void debuggingDisplay(sf::RenderTarget& targetWindow) const;

    double viewRange; ///< Vision cone width.
    double viewDistance; ///< Vision cone depth.

    /**
     * @brief Returns closest target.
     */
    Vec2d getClosestTarget(const std::list<Vec2d>& targetsInSight)const;

    currentState current_state; ///< Current behavioural state.

    /**
     * @brief Returns a list of the foods in sight.
     */
    std::list<OrganicEntity*> foodInSight(const std::list<OrganicEntity*> entitiesInSight) const;

    /**
     * @brief Returns a list of the mates in sight.
     */
    std::list<OrganicEntity*> mateInSight(const std::list<OrganicEntity*> entitiesInSight) const;

    /**
     * @brief Returns a list of the predators in sight.
     */
    std::list<OrganicEntity*> predatorsInSight(const std::list<OrganicEntity*> entitiesInSight) const;


    // ─ Biological flags ─
    bool isFemale;
    bool isFeeding;
    bool isMating;
    bool isPregnant;
    bool isGestating;
    bool isDelivering;

    // ─ Timers ─
    sf::Time feeding_counter;
    sf::Time mating_counter;
    sf::Time gestating_counter;
    sf::Time delivering_counter;

    // ─ Entities In Environment Containers ─
    std::list<OrganicEntity*> food_in_sight;
    std::list<OrganicEntity*> mate_in_sight;
    std::list<OrganicEntity*> predators_in_sight;

    /**
     * @brief Pure virtual method with which subclasses instantiate offspring.
     */
    virtual void giving_birth() = 0;

    int nb_babies; ///< Babies to be delivered.

    DrawingPriority getDepth() const override;

    // ─ Pure virtual functions that get constants polymorphically ─
    virtual double getViewRange() const = 0;
    virtual double getViewDistance() const = 0;
    virtual double getRandomWalkRadius() const = 0;
    virtual double getRandomWalkDistance() const = 0;
    virtual double getRandomWalkJitter() const = 0;
    virtual double getGestatingTime() const = 0;

    /**
     * @brief Updates movement in function of acceleration and time.
     * @param acceleration Force-based acceleration vector.
     */
    void movementUpdate(const Vec2d& acceleration, double elapsedTime);

    /**
     * @brief Treats predator in sight behaviour.
     */
    void predatorInSightBehaviour(double elapsedTime);

    /**
     * @brief Treats feeding behaviour.
     */
    void feedingBehaviour(sf::Time dt);

    /**
     * @brief Treats mating behaviour.
     */
    void matingBehaviour(sf::Time dt);

    /**
     * @brief Treats delivering behaviour.
     */
    void deliveringBehaviour(sf::Time dt);

    /**
     * @brief Treats gestating behaviour.
     */
    void gestatingBehaviour(sf::Time dt);

    /**
     * @brief Adds the position of the predators in memory.
     */
    void predatorInSightPositions();

    /**
     * @brief Switches between MATING and MATE_IN_SIGHT depending on the
     * distance of the mate.
     */
    void matingTreatment(OrganicEntity* closest_entity);

    /**
     * @brief Switches between FEEDING and FOOD_IN_SIGHT depending on the
     * distance of the food.
     */
    void feedingTreatment(OrganicEntity* closest_entity);

    /**
     * @brief Returns maximum speed.
     */
    double getMaxSpeed() const;

    /**
     * @brief updates the energy of animals in function of time.
     */
    void updateEnergy(double elapsed_time);

    /**
     * @brief returns current state of animal.
     */
    currentState getCurrentState() const;

    /**
     * @brief returns current direction of animal.
     */
    Vec2d getDirection() const;

    /**
     * @brief sets current speed of animal.
     */
    void setSpeed(double new_speed);

    /**
     * @brief updates current speed of animal.
     * @note we didn't modularize this method more because fo the returns.
     */
    void updateState(sf::Time dt);

    /**
     * @brief Updates the predator positions list.
     */
    void setPredatorsPositions (const std::list<Vec2d>& newpositions);

    /**
     * @brief Updates the deceleration mode.
     */
    void setDecelerationMode(DecelerationMode mode);

    // ─ Debug overlays ─

    /**
     * @brief Draws a label for energy level.
     */
    void drawEnergy(sf::RenderTarget& targetWindow) const;

    /**
     * @brief Draws a label for sex.
     */
    void drawSex(sf::RenderTarget& targetWindow) const;

    /**
     * @brief Draws a label for current state.
     */
    void drawState(sf::RenderTarget& targetWindow) const;

    /**
     * @brief Draws a ring to indicate pregnancy.
     */
    void drawPregnancy(sf::RenderTarget& targetWindow) const;

};
