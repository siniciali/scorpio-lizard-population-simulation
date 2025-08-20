#include "../Animal/NeuronalScorpion/NeuronalScorpion.hpp"
#include "../Animal/NeuronalScorpion/Sensor.hpp"
#include "../Application.hpp"
#include "../Utility/Utility.hpp"

void NeuronalScorpion::sensorConstruction()
{

    // Step 1: Create and attach 8 sensors with their angular position
    const std::array<size_t, 3> INDEXES({3,4,5});
    for (size_t i(0); i<8; ++i) {
        sensors[i].first = new Sensor(this,i);
        sensors[i].second = SENSOR_POSITIONS[i];
    }

    // Step 2: Each sensor inhibits 3 "opposite-side" sensors
    for (size_t i(0); i<8; ++i) {
        for(size_t j(0); j<=2; ++j) {
            sensors[i].first->addAssociatedSensors(sensors[ (i+INDEXES[j]) % 8 ].first, j);
        }
    }

}

NeuronalScorpion::NeuronalScorpion(const Vec2d& initialPosition, double energyLvl, bool isFemale)
    : Scorpion(initialPosition, energyLvl, isFemale),
      idle_time(sf::Time::Zero),
      moving_time(sf::Time::Zero),
      current_state_ns(WANDERING_)
{
    sensorConstruction();
}

NeuronalScorpion::NeuronalScorpion(const Vec2d& initialPosition)
    : Scorpion(initialPosition),
      current_state_ns(WANDERING_)
{
    sensorConstruction();
}

NeuronalScorpion::~NeuronalScorpion()
{
    for (auto& entry : sensors) {
        delete entry.first;
        entry.first = nullptr;
    }
};

Vec2d NeuronalScorpion::getPositionOfSensor(size_t chosen_sensor) const
{
    double alpha = SENSOR_POSITIONS[chosen_sensor] * DEG_TO_RAD;
    double theta = getRotation() * DEG_TO_RAD;
    double sensor_radius = getAppConfig().scorpion_sensor_radius;
    Vec2d local_position(std::cos(alpha+theta)*sensor_radius,
                         std::sin(alpha+theta)*sensor_radius);
    return convertToGlobalCoord(local_position);
}

void NeuronalScorpion::setDirectionEstimation()
{
    Vec2d res(0.0, 0.0);
    for (size_t i(0); i<8; ++i) {
        res+=sensors[i].first->getScore()*(getPositionOfSensor(i)-getPosition());
    }
    direction_estimation = res;
    direction_estimation_score = res.length();
}

void NeuronalScorpion::update(sf::Time dt)
{
    for (auto& p : sensors) {
        p.first->update(dt);
    }

    double elapsed_time = dt.asSeconds();
    updateState(dt);
    switch (current_state_ns) {

    case TARGET_IN_SIGHT:
        targetInSightBehaviour(elapsed_time);
        break;

    case WANDERING_:
        randomWalk(elapsed_time);
        break;

    case MOVING:
        movingBehaviour(dt);
        break;

    case IDLE:
        idleBehaviour(dt);
        break;
    }
}

void NeuronalScorpion::idleUpdateState()
{
    if (direction_estimation_score >= getAppConfig().scorpion_minimal_score_for_action) {
        current_state_ns = MOVING;
        moving_time = sf::Time::Zero;
        isIdle=false;
        isMoving = true;
    }
    if (idle_time.asSeconds() >= getAppConfig().neuronal_scorpion_idle_time) {
        current_state_ns = WANDERING_;
        isIdle=false;
    }
}

void NeuronalScorpion::movingUpdateState(sf::Time dt)
{
    moving_time += dt;
    if (moving_time.asSeconds() >= getAppConfig().neuronal_scorpion_moving_time) {
        current_state_ns = IDLE;
        idle_time = sf::Time::Zero;
        moving_time = sf::Time::Zero;
        isMoving=false;
        isIdle = true;
        direction_estimation = Vec2d(0,0);
        direction_estimation_score = 0.0;
    }
}

void NeuronalScorpion::updateState(sf::Time dt)
{
    analyzeEnvironment(getAppEnv().getEntitiesInSightForAnimal(this));

    // Priority: food in sight triggers direct chase behavior
    OrganicEntity* closestEntity (getClosestEntity(this->getFoodInSight()));
    if (closestEntity != nullptr) {
        setTargetPosition(closestEntity->getPosition());
        current_state_ns = TARGET_IN_SIGHT;
        return;
    }

    // No food in sight: use sensory input to transition between IDLE, MOVING, and WANDERING
    switch (current_state_ns) {
    case IDLE: {
        idleUpdateState();
        break;
    }
    case MOVING: {
        movingUpdateState(dt);
        break;
    }
    case WANDERING_: {
        for (const auto& p : sensors)
            if (p.first->getIfActive()) {
                current_state_ns = IDLE;
                idle_time = sf::Time::Zero;
                isIdle = true;
                break;
            }
        break;
    }
    case TARGET_IN_SIGHT: {
        current_state_ns = IDLE;
        idle_time = sf::Time::Zero;
        isIdle = true;
        break;
    }
    }
}

void NeuronalScorpion::movingBehaviour(sf::Time dt)
{
    if (!isMoving) {
        isMoving    = true;
        moving_time = sf::Time::Zero;
    }

    if (std::abs(direction_estimation.angle() - getRotation()) >= getAppConfig().scorpion_rotation_angle_precision) {
        setRotation(direction_estimation.angle());
    } else {
        Vec2d target = convertToGlobalCoord(direction_estimation);
        Vec2d acceleration = getAttractionForce(target)/getMass();
        Vec2d newSpeed = getSpeedVector() + acceleration * dt.asSeconds();
        this->move(newSpeed*dt.asSeconds());
    }
}

void NeuronalScorpion::idleBehaviour(sf::Time dt)
{
    if(!isIdle) {
        isIdle = true;
        idle_time = sf::Time::Zero;
    }
    if(isIdle) {
        idle_time += dt;
    }
}

void NeuronalScorpion::debuggingDisplay(sf::RenderTarget& targetWindow) const
{
    drawVision(targetWindow);
    drawHitbox(targetWindow);
    for (size_t i (0); i < 8; ++i) {
        sf::Color sensor_color (sensors[i].first->getSensorColor());
        Vec2d sensor_position (getPositionOfSensor(i));
        targetWindow.draw(buildCircle(sensor_position, 0.25*getRadius(), sensor_color));
    }
    std::string state;
    sf::Color statecolor;
    switch (current_state_ns) {
    default:
        break;
    case WANDERING_:
        state = "WANDERING";
        statecolor = sf::Color::Black;
        break;
    case TARGET_IN_SIGHT:
        state = "TARGET IN SIGHT";
        statecolor = sf::Color::Black;
        break;
    case IDLE:
        state = "IDLE";
        statecolor = sf::Color::Black;
        break;
    case MOVING:
        state = "MOVING";
        statecolor = sf::Color::Black;
        break;
    }
    auto statetext = buildText(state,
                               convertToGlobalCoord(Vec2d(getRandomWalkDistance() + 125, 0)),
                               getAppFont(),
                               getAppConfig().default_debug_text_size,
                               statecolor,
                               this->getRotation()/ DEG_TO_RAD + 90
                              );
    targetWindow.draw(statetext);
}

std::array<std::pair<Sensor*, double>,8> NeuronalScorpion::getSensors() const
{
    return sensors;
}

void NeuronalScorpion::incrementCounter() const
{
    getAppEnv().incrementNS();
}
