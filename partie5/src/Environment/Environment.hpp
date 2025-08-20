#pragma once
#include <list>

#include "../Utility/Vec2d.hpp"
#include <SFML/Graphics.hpp>
#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include <algorithm>

class OrganicEntity;
class Animal;
class CloudGenerator;
class Cloud;
class Wave;
class Collider;

/**
 * @brief Represents the simulation environment where all dynamic entities evolve.
 *
 * This class acts as a container and orchestrator for entities, clouds, waves,
 * obstacles, and the environmental state such as temperature and humidity.
 * It also manages their lifetimes, rendering, and updates.
 */
class Environment : public Drawable, public Updatable
{
public:
    /**
     * @brief Default constructor initializing temperature and timers.
     */
    Environment();

    /**
     * @brief Destructor that ensures all dynamically allocated entities are deleted.
     */
    ~Environment();

    // Disable copy constructor and assignment (manual memory management)
    Environment(const Environment& autreEnvironnement) = delete;
    Environment& operator=(const Environment& autreEnvironnement) = delete;

    // === Temperature control ===

    /**
     * @brief Increases the environment's temperature, respecting the upper limit.
     */
    void increaseTemperature();

    /**
     * @brief Returns the current temperature.
     */
    double getTemperature() const;

    /**
     * @brief Decreases the environment's temperature, respecting the lower limit.
     */
    void decreaseTemperature();

    /**
     * @brief Resets temperature to default from configuration.
     */
    void resetControls();

    // === Entity management ===

    /**
     * @brief Adds a new organic entity to the environment.
     * @param newentity Pointer to the OrganicEntity to be added. The Environment takes ownership.
     */
    void addEntity(OrganicEntity* newentity);

    /**
     * @brief Returns a list of organic entities visible to the given animal.
     * @param animal Pointer to the animal observing its surroundings.
     * @return A list of OrganicEntity pointers currently visible to the animal.
     */
    std::list <OrganicEntity*> getEntitiesInSightForAnimal(Animal* animal) const;

    // === Cloud and rain control ===

    /**
     * @brief Adds a cloud generator to the environment.
     * @param new_cloud_generator Pointer to a CloudGenerator.
     */
    void addGenerator(CloudGenerator* new_cloud_generator);

    /**
     * @brief Creates a new cloud at the given position with the specified radius.
     * @param position Center of the new cloud.
     * @param radius Radius of the cloud (must be non-negative).
     */
    void createCloud(const Vec2d& position, double radius);

    // === Simulation update/render interface ===

    /**
     * @brief Updates all internal components (entities, clouds, waves, etc.).
     */
    void update(sf::Time dt);

    /**
     * @brief Renders all visible components to the given render target.
     */
    void draw(sf::RenderTarget& targetWindow) const;

    /**
     * @brief Deletes and clears all internal objects.
     */
    void clean();


    // === Environmental state query ===

    /**
     * @brief Returns the current drought time.
     */
    sf::Time getDroughtTime() const;

    /**
     * @brief Returns the current cloud number.
     */
    double getCloudNumber() const;

    /**
     * @brief Returns if the weather is humid.
     */
    bool getHumidity() const;

    // === Waves and obstacles ===

    /**
     * @brief Adds a new wave to the environment.
     * @param new_wave Pointer to the Wave object to be added.
     */
    void addWave(Wave* new_wave);

    /**
     * @brief Adds a new obstacle (Collider) to the environment.
     * @param new_obstacle Pointer to a Collider.
     */
    void addObstacle(Collider* new_obstacle);

    /**
     * @brief Computes the cumulative intensity of waves at a given location.
     * @param location The position in the environment where intensity is measured.
     * @return The total intensity resulting from nearby waves.
     */
    double getIntensitySumAt(const Vec2d& location) const;

    /**
     * @brief Fetches environment statistics by category (e.g., number of lizards, waves).
     * @param title A string identifier for the data group requested.
     * @return A map of string keys and their associated values (e.g., species count).
     */
    std::unordered_map<std::string, double> fetchData(const std::string& title) const;

    /**
     * @brief Increments Scopion Counter.
     */
    void incrementScorpionCounter();
    /**
     * @brief Increments Lizard Counter.
     */
    void incrementLizardCounter();
    /**
     * @brief Increments Cactus Counter.
     */
    void incrementCactusCounter();

    /**
     * @brief Increments NeuronalScorpion counter.
     */
    void incrementNS();
    /**
     * @brief Increments WaveLizard counter.
     */
    void incrementWL();

private:

    // === Core containers ===
    std::list <OrganicEntity*> entities;
    std::list <CloudGenerator*> cloud_generators;
    std::list<Cloud*> clouds;
    std::list<Wave*> waves;
    std::list<Collider*> obstacles;

    // === Environmental state ===
    double temperature;

    sf::Time droughtTime;
    sf::Time rainingTime;
    sf::Time humidityTime;

    bool isRaining;
    bool isHumid;

    // === Entity counters ===
    size_t scorpionCounter;
    size_t lizardCounter;
    size_t cactusCounter;
    size_t NSCounter;
    size_t WLCounter;

    // === Internal update helpers (most of parameters are the time step dt) ===
    void modelizeRaining(sf::Time dt);
    void modelizeHumidity(sf::Time dt);

    void waveUpdate(sf::Time dt);
    void entityUpdate(sf::Time dt);
    void cloudUpdate(sf::Time dt);
    void countersUpdate();

};
