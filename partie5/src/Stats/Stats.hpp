#pragma once

#include "../Interface/Drawable.hpp"
#include "../Interface/Updatable.hpp"
#include "Graph.hpp"
#include <memory>
#include <map>
#include <string>

/**
 * @brief Manages and displays statistical graphs in the simulation.
 *
 * The Stats class handles multiple Graph objects, allowing switching between them,
 * updating their data, and rendering the currently active graph.
 */
class Stats : public Drawable, public Updatable
{
public:
    /**
     * @brief Constructs a Stats manager with default graph titles.
     */
    Stats();

    /**
     * @brief Destructor for Stats.
     */
    ~Stats() override;

    /**
     * @brief Draws the currently active graph to the target window.
     * @param target The render target where the graph will be drawn.
     */
    void draw(sf::RenderTarget& target) const override final;

    /**
     * @brief Sets the active graph by its ID.
     * @param id The ID of the graph to activate.
     */
    void setActive(int id);

    /**
     * @brief Gets the title of the currently active graph.
     * @return The title string of the active graph.
     */
    std::string getCurrentTitle() const;

    /**
     * @brief Switches to the next graph in the list.
     */
    void next();

    /**
     * @brief Switches to the previous graph in the list.
     */
    void previous();

    /**
     * @brief Focuses on a graph by its title and resets its data.
     * @param graph_title The title of the graph to focus on.
     */
    void focusOn(const std::string graph_title);

    /**
     * @brief Resets all graphs to their initial state.
     */
    void reset();

    /**
     * @brief Adds a new graph to the Stats manager.
     * @param id Unique identifier for the graph.
     * @param title Title of the graph.
     * @param series List of data series names.
     * @param min Minimum Y-axis value.
     * @param max Maximum Y-axis value.
     * @param size Size of the graph on screen.
     */
    void addGraph(int id,
                  const std::string &title,
                  const std::vector<std::string> &series,
                  double min,
                  double max,
                  const Vec2d &size);

    /**
     * @brief Updates the active graph with new data at a fixed refresh rate.
     * @param dt Time elapsed since the last update.
     */
    void update(sf::Time dt) override final;

private:
    int active_key; ///< ID of the currently active graph.
    std::map<int, std::unique_ptr<Graph>> graphs; ///< Map of graph IDs to Graph objects.
    std::map<int, std::string> titles; ///< Map of graph IDs to their titles.
    sf::Time refresh_rate_counter; ///< Counter to manage update frequency.
};
