#include "../Animal/Animal.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"
#include "../Utility/Constants.hpp"
#include "../Utility/Vec2d.hpp"
#include "../algorithm"
#include "../limits"
#include "../Utility/Arc.hpp"
#include "../Random/Random.hpp"
#include <cmath>


Animal::Animal(const Vec2d& position, double size, double energyLvl, bool isfemale)

    :
    OrganicEntity(position, size, energyLvl),
    speed (0.0),
    targetPosition (0, 0),
    direction (1, 0),
    current_state (WANDERING),
    isFemale(isfemale),
    isFeeding(false),
    isMating(false),
    isPregnant(false),
    isGestating(false),
    isDelivering(false),
    feeding_counter(sf::Time::Zero),
    nb_babies(0)


{}

Animal::~Animal()
{

}

//double Animal::getStandardMaxSpeed()const{
//    return ANIMAL_MAX_SPEED;
//}

//double Animal::getMass()const{
//    return  ANIMAL_MASS;
//}

void Animal::setTargetPosition (const Vec2d& newPosition)
{
    targetPosition = newPosition;
}

void Animal::setPredatorsPositions (const std::list <Vec2d>& newpositions)
{
    predators_positions = newpositions;
}

Vec2d Animal::getSpeedVector () const
{
    Vec2d res(direction.x()*speed,direction.y()*speed);
    return res;
}

void Animal::debuggingDisplay(sf::RenderTarget& targetWindow) const
{

    drawVision(targetWindow);
    auto color(sf::Color(20,150,20,30));
    targetWindow.draw(buildCircle(getPosition(), getRadius(), color));

    auto energytext = buildText(to_nice_string(getEnergyLevel()),
                                convertToGlobalCoord(Vec2d(getRandomWalkDistance()+35, 0)),
                                getAppFont(),
                                getAppConfig().default_debug_text_size,
                                sf::Color::Black,
                                this->getRotation()/ DEG_TO_RAD + 90
                               );

    std::string sex;
    if(isFemale) {
        sex = "Female";
    } else {
        sex = "Male";
    }
    auto sextext = buildText(sex,
                             convertToGlobalCoord(Vec2d(getRandomWalkDistance()+70, 0)),
                             getAppFont(),
                             getAppConfig().default_debug_text_size,
                             sf::Color::Black,
                             this->getRotation()/ DEG_TO_RAD + 90
                            );

    if (isFemale and isPregnant) {

        targetWindow.draw(buildAnnulus(getPosition(),
                                       getRadius() + 5.0,
                                       sf::Color::Magenta,
                                       3));
    }


    std::string state;
    sf::Color statecolor;
    switch (current_state) {
    default:
        break;
    case WANDERING:
        state = "WANDERING";
        statecolor = sf::Color::Black;
        break;
    case FOOD_IN_SIGHT:
        state = "FOOD IN SIGHT";
        statecolor = sf::Color::Blue;
        break;
    case FEEDING:
        state = "FEEDING";
        statecolor = sf::Color::Green;
        break;
    case RUNNING_AWAY:
        state = "RUNNING AWAY";
        statecolor = sf::Color::Red;
        break;
    case MATE_IN_SIGHT:
        state = "MATE IN SIGHT";
        statecolor = sf::Color::Cyan;
        break;

    case MATING:
        state = "MATING";
        statecolor = sf::Color::Magenta;
        break;
    case GIVING_BIRTH:
        state = "GIVING BIRTH";
        statecolor = sf::Color::White;
        break;
        //TO BE IMPLEMENTED
    }

    auto statetext = buildText(state,
                               convertToGlobalCoord(Vec2d(getRandomWalkDistance(), 0)),
                               getAppFont(),
                               getAppConfig().default_debug_text_size,
                               statecolor,
                               this->getRotation()/ DEG_TO_RAD + 90
                              );

    targetWindow.draw(energytext);
    targetWindow.draw(sextext);
    targetWindow.draw(statetext);
}

void Animal::draw(sf::RenderTarget& targetWindow)const
{

    if(isDebugOn()) {

        debuggingDisplay(targetWindow);

    }

    // dessiner le Sprite

    auto image_to_draw(buildSprite(this->getPosition(),
                                   (this->getRadius()*2),
                                   getAppTexture(this->getTexture()),
                                   this->getRotation() /DEG_TO_RAD));
    targetWindow.draw(image_to_draw);
    //targetWindow.draw(buildCircle(targetPosition, 5.0, sf::Color(255, 0, 0)));

}

DrawingPriority Animal::getDepth() const
{
    return DrawingPriority::ANIMAL_PRIORITY;
}

void Animal::setDecelerationMode(DecelerationMode mode)
{
    currentDeceleration = mode;
}

double Animal::getDeceleration(const DecelerationMode& mode) const
{

    if (mode==Weak) {
        return 0.3;
    } else if (mode==Strong) {
        return 0.9;
    }

    else {
        return 0.6;
    }

}

double Animal::getMaxSpeed() const
{
    double maxSpeed;
    switch (current_state) {
    case FOOD_IN_SIGHT: {
        maxSpeed = 3*getStandardMaxSpeed();
        break;
    }
    case MATE_IN_SIGHT: {
        maxSpeed = 2*getStandardMaxSpeed();
        break;
    }
    case RUNNING_AWAY: {
        maxSpeed = 4*getStandardMaxSpeed();
        break;
    }
    default: {
        maxSpeed = getStandardMaxSpeed();
        break;
    }
    }

    if (getEnergyLevel() < 0.25*getInitialEnergy()) {
        return 0.33*maxSpeed; // if the energy level goes below 25% of the initial level,
        // the animal will walk with one third of the initial speed.
        //
    } else {
        return maxSpeed;
    }
}

Vec2d Animal::getAttractionForce(const Vec2d& chosenTarget) const
{

    Vec2d res;

    Vec2d vectToTarget=chosenTarget-this->getPosition();

    if (vectToTarget.length() == 0) {
        return Vec2d(0, 0);
    }

    double wantedSpeed = std::min((vectToTarget.length() / getDeceleration(currentDeceleration)), getMaxSpeed());

    Vec2d vTarget(vectToTarget*wantedSpeed/vectToTarget.length());

    res=vTarget-getSpeedVector();

    return res;
}

Vec2d Animal::getRepulsionForce(const std::list<Vec2d>& predators) const
{

    Vec2d res (0, 0);
    double delta1 = 500.0; // amplification coefficient
    double delta2 = 1.2; // repulsion impact coefficient
    for (const auto& pred : predators) {

        Vec2d vectToPred = this->getPosition() - pred;

        if (isEqual(vectToPred.lengthSquared(), 0.0)) continue; // avoid dviding by 0

        Vec2d f = (delta1*vectToPred) / pow(vectToPred.length(), delta2);
        res += f;
    }


    return  res;
}


//double Animal::getRandomWalkRadius() const{
//    return ANIMAL_RANDOM_WALK_RADIUS;
//}

//double Animal::getRandomWalkDistance() const{
//    return ANIMAL_RANDOM_WALK_DISTANCE;
//}

//double Animal::getRandomWalkJitter() const{
//    return ANIMAL_RANDOM_WALK_JITTER;
//}

Vec2d Animal::convertToGlobalCoord(const Vec2d& local)const
{
    // create a transformation matrix
    sf::Transform matTransform;

    // first, translate
    matTransform.translate(getPosition());

    // then rotate
    matTransform.rotate(getRotation()/DEG_TO_RAD);

    // now transform the point
    Vec2d global = matTransform.transformPoint(local);
    return global;
}

void Animal::randomWalk(double elapsedTime)
{


    Vec2d random_vec (uniform(-1.0,1.0),uniform(-1.0,1.0));
    current_target += random_vec * getRandomWalkJitter();
    current_target = current_target.normalised()*getRandomWalkRadius();

    Vec2d moved_current_target = current_target + Vec2d(getRandomWalkDistance(), 0);

    Vec2d acceleration = getAttractionForce(convertToGlobalCoord(moved_current_target)) / getMass();

    Vec2d newSpeed = getSpeedVector() + acceleration * elapsedTime;

    if (newSpeed.length() > getMaxSpeed()) {
        newSpeed = newSpeed.normalised() * getMaxSpeed();
    }

    if (!isEqual(newSpeed.length(),0.0)) {
        direction = newSpeed.normalised();
        speed=newSpeed.length();
    }


    this->move(newSpeed*elapsedTime);
}

bool Animal::getIfIsFemale() const
{

    return isFemale;

}

std::list<OrganicEntity*> Animal::foodInSight(const std::list<OrganicEntity*> entitiesInSight) const
{

    std::list <OrganicEntity*> visible_food;
    for (const auto& entity : entitiesInSight) {

        if (entity != nullptr and this->eatable(entity)) {

            visible_food.push_back(entity);

        }
    }
    return visible_food;
}

std::list<OrganicEntity*> Animal::mateInSight(const std::list<OrganicEntity*> entitiesInSight) const
{

    std::list <OrganicEntity*> visible_mate;
    for (const auto& entity : entitiesInSight) {

        if (entity != nullptr and this->matable(entity)) {

            visible_mate.push_back(entity);

        }
    }
    return visible_mate;
}

std::list<OrganicEntity*> Animal::predatorsInSight(const std::list<OrganicEntity*> entitiesInSight) const
{

    std::list <OrganicEntity*> visible_predators;
    for (const auto& entity : entitiesInSight) {

        if (entity != nullptr and entity->eatable(this)) {

            visible_predators.push_back(entity);

        }
    }
    return visible_predators;
}

void Animal::updateEnergy(double elapsed_time)
{
    double lost_energy = getAppConfig().animal_base_energy_consumption
                         + getSpeedVector().length() * getEnergyLossFactor() * elapsed_time;
    setEnergyLevel(getEnergyLevel()-lost_energy);
}

void Animal::analyzeEnvironment(std::list <OrganicEntity*> entitiesInSight)
{

    mate_in_sight = mateInSight(entitiesInSight);
    food_in_sight = foodInSight(entitiesInSight);
    predators_in_sight = predatorsInSight(entitiesInSight);

}

void Animal::updateState(sf::Time dt)
{


    for (const auto& predator : predators_positions) {

        double distance = (predator - getPosition()).length();

        if (distance/getAppConfig().simulation_world_size < 0.5) {
            current_state = RUNNING_AWAY;
            return;
        }
    }



    if(isDelivering) {
        current_state = GIVING_BIRTH;
        return;
    }

    if(isGestating) {

        current_state = WANDERING;
        gestating_counter+=dt;

        if((gestating_counter).asSeconds() >= this->getGestatingTime()) {
            isGestating=false;


            isDelivering= true;
        }

        return;
    }

    std::list <OrganicEntity*> entitiesInSight = getAppEnv().getEntitiesInSightForAnimal(this);

    analyzeEnvironment(entitiesInSight);


    if (food_in_sight.empty() and mate_in_sight.empty() and predators_in_sight.empty()) {

        current_state = WANDERING;
        return;
    }

    if(!(predators_in_sight.empty())) {

        std::list <Vec2d> predators_in_sight_positions;

        for (const auto& predator : predators_in_sight) {

            Vec2d predposition (predator->getPosition());
            predators_in_sight_positions.push_back(predposition);

        }

        setPredatorsPositions(predators_in_sight_positions);

        current_state = RUNNING_AWAY;

    }

    if (!(mate_in_sight.empty())) {

        OrganicEntity* closest_entity=getClosestEntity(mate_in_sight);


        if (closest_entity == nullptr) {

            current_state = WANDERING;

            return;

        }
        if (this->isColliding(*closest_entity)) {

            if(!isMating) {
                this->meet(closest_entity);
            }

            current_state = MATING;


        }

        else {


            Vec2d chosenTarget(closest_entity->getPosition());

            setTargetPosition(chosenTarget); // chosen target must be a Vec2d
            current_state = MATE_IN_SIGHT;


        }
        return;

    }

    if (!(food_in_sight.empty())) {


        OrganicEntity* closest_entity=getClosestEntity(food_in_sight);
        if (closest_entity == nullptr) {

            current_state = WANDERING;

            return;
        }

        if (this->isColliding(*closest_entity)) {

            current_state = FEEDING;


        }

        else {

            Vec2d chosenTarget(closest_entity->getPosition());
            setTargetPosition(chosenTarget);

            current_state = FOOD_IN_SIGHT;

        }

        return;


    }


}

void Animal::targetInSightBehaviour(double elapsedTime)
{

    Vec2d acceleration = getAttractionForce(targetPosition) / getMass();

    Vec2d newSpeed = getSpeedVector() + acceleration * elapsedTime;

    if (newSpeed.length() > getMaxSpeed()) {
        newSpeed = newSpeed.normalised() * getMaxSpeed();
    }

    if (!isEqual(newSpeed.length(),0.0)) {
        direction = newSpeed.normalised();
        speed=newSpeed.length();
    }

    this->move(newSpeed*elapsedTime);

}

void Animal::predatorInSightBehaviour(double elapsedTime)
{

    Vec2d acceleration = getRepulsionForce(predators_positions) / getMass();

    Vec2d newSpeed = (getSpeedVector() + acceleration * elapsedTime);

    if (newSpeed.length() > getMaxSpeed()) {
        newSpeed = newSpeed.normalised() * getMaxSpeed();
    }

    if (!isEqual(newSpeed.length(),0.0)) {
        direction =  newSpeed.normalised();
        speed= newSpeed.length();
    }

    this->move(newSpeed*elapsedTime);



}
void Animal::feedingBehaviour(sf::Time dt)
{

    if(!isFeeding) {

        isFeeding = true;
        feeding_counter = sf::Time::Zero;
        this->setEnergyLevel(this->getEnergyLevel()+getAppConfig().animal_meal_retention);
        OrganicEntity* closest_entity = getClosestEntity(foodInSight(getAppEnv().getEntitiesInSightForAnimal(this)));

        if(closest_entity != nullptr) {

            closest_entity->setEatenEnergy();

        }

    }



    if(isFeeding) {

        feeding_counter += dt;

        if(feeding_counter > sf::seconds(getAppConfig().animal_eating_pause_time)) {

            isFeeding=false;
            feeding_counter = sf::Time::Zero;
            current_state = WANDERING;

        }
    }

}

void Animal::matingBehaviour(sf::Time dt)
{

    if(!isMating) {

        isMating = true;
        mating_counter = sf::Time::Zero;

    }

    mating_counter += dt;

    //if(mating_counter < sf::seconds(getAppConfig().animal_mating_pause_time)){
    //    return;
    //}

    if(mating_counter > sf::seconds(getAppConfig().animal_mating_pause_time)) {

        isMating=false;


        mating_counter = sf::Time::Zero;

        if (getIfIsFemale()) {

            setPregnancy(true);
            isGestating=true;
            gestating_counter = sf::Time::Zero;

        }

        current_state = WANDERING;

    }
}



void Animal::deliveringBehaviour(sf::Time dt)
{

    if(!isDelivering) {

        isDelivering = true;
        delivering_counter = sf::Time::Zero;

    }

    //if(delivering_counter < sf::seconds(getAppConfig().animal_delivery_pause_time)){
    //    return;
    //}

    delivering_counter += dt;

    if(delivering_counter > sf::seconds(getAppConfig().animal_delivery_pause_time)) {

        for (int i(0); i < nb_babies; i++) {
            this->giving_birth();
        }

        isDelivering=false;

        isPregnant=false;


        delivering_counter = sf::Time::Zero;


    }
}



void Animal::update(sf::Time dt)
{



    double elapsedTime = dt.asSeconds();

    if (current_state != FEEDING) { // selon les videos du test tant que l'animal mange il ne perd pas d'énergie

        updateEnergy(elapsedTime);

    }

    this->updateState(dt);

    switch (current_state) {

    case FOOD_IN_SIGHT: {

        targetInSightBehaviour(elapsedTime);

        break;
    }

    case WANDERING: {

        this->randomWalk(elapsedTime);

        break;


    }
    case FEEDING: {

        feedingBehaviour(dt);

        break;
    }
    case MATE_IN_SIGHT: {

        targetInSightBehaviour(elapsedTime);

        break;

    }

    case MATING: {

        matingBehaviour(dt);

        break;

    }

    case GIVING_BIRTH: {

        deliveringBehaviour(dt);

        break;

    }
    case RUNNING_AWAY: {

        predatorInSightBehaviour(elapsedTime);

        break;
    }
    default : {
        break;
    }
        // TODO: OTHER CASES
    }



    OrganicEntity::update(dt);

}


//double Animal::getViewRange() const{
//    return ANIMAL_VIEW_RANGE;
//}

//double Animal::getViewDistance() const{
//    return ANIMAL_VIEW_DISTANCE;
//}

double Animal::getRotation() const
{
    return direction.angle();
}

void Animal::setRotation(const double& angle)
{
    direction = {cos(angle), sin(angle)};
}

void Animal::setDirection(const Vec2d& dir)
{
    if (dir.lengthSquared()!=0) {

        direction=dir.normalised();
    }

}

void Animal::drawVision(sf::RenderTarget& targetWindow)const
{

    sf::Color color = sf::Color::Black;
    color.a = 16; // light, transparent grey
    targetWindow.draw(buildArc((-getViewRange()/2)/ DEG_TO_RAD, (getViewRange()/2)/DEG_TO_RAD, getViewDistance(), getPosition(), color, this->getRotation()/ DEG_TO_RAD));

    if (!isTargetInSight(targetPosition)) {

        targetWindow.draw(buildAnnulus(convertToGlobalCoord(Vec2d(getRandomWalkDistance(), 0)), getRandomWalkRadius(), sf::Color(255, 150, 0), 2));
        targetWindow.draw(buildCircle(convertToGlobalCoord(current_target + Vec2d(getRandomWalkDistance(), 0)), 5.0, sf::Color(0, 0, 255)));

    }


}

bool Animal::isTargetInSight(const Vec2d& wantedTargetPosition) const
{

    Vec2d animalToTarget = (wantedTargetPosition - getPosition());

    if (isEqual(animalToTarget.lengthSquared(), 0.0)) {
        return true;
    }

    return ((animalToTarget.lengthSquared() <= getViewDistance()*getViewDistance())
            and ((direction.dot(animalToTarget.normalised()))>= cos((getViewRange()+ 0.001)/2)));


}

Vec2d Animal::getClosestTarget(const std::list <Vec2d>& targetsInSight) const
{

    double minDistance(std::numeric_limits<double>::infinity());
    Vec2d closestTarget;

    for (const auto& target : targetsInSight) {


        if ((minDistance*minDistance)>(target - this->getPosition()).lengthSquared()) {
            minDistance=(target - this->getPosition()).length();
            closestTarget=target;
        }

    }

    return closestTarget;
}

OrganicEntity* Animal::getClosestEntity(const std::list <OrganicEntity*>& entitiesInSight) const
{

    double minDistanceSquared(std::numeric_limits<double>::infinity());

    OrganicEntity* closestEntity = nullptr;

    for (const auto& entity : entitiesInSight) {

        if ((minDistanceSquared)>(entity->getPosition()-this->getPosition()).lengthSquared()) { //lengthSquared() procure un calcul plus optimal
            minDistanceSquared=((entity->getPosition()-this->getPosition()).lengthSquared());
            closestEntity=entity;
        }

    }

    return closestEntity;

}

bool Animal::getIfPregnant() const
{
    return isPregnant;
}

bool Animal::getIfGestating() const
{

    return isGestating;
}

void Animal::setPregnancy(bool pregnancy)
{
    isPregnant = pregnancy;
}

void Animal::setNumberBabies(int nbBabies)
{
    nb_babies = nbBabies;
}

void Animal::setGestatingCounter(sf::Time counter)
{
    gestating_counter = counter;
}

int Animal::getNumberBabies() const
{
    return nb_babies;
}

bool Animal::getIfIsDelivering() const
{
    return isDelivering;
}
