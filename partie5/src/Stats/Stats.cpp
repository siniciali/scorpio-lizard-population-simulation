#include "Stats.hpp"
#include "../Application.hpp"
#include "../Environment/Environment.hpp"

Stats::Stats() :
    active_key(0), // Default active graph is GENERAL
    titles{{0, s::GENERAL}, {1, s::WAVES}},
refresh_rate_counter(sf::Time::Zero) // Initialize refresh timer
{}

Stats::~Stats() {}

void Stats::draw(sf::RenderTarget& target) const
{
    graphs.at(active_key)->draw(target);
}

void Stats::setActive(int id)
{
    // Only set active if the ID exists in the titles map and the graphs map
    if (titles.find(id) != titles.end() and graphs.find(id) != graphs.end()) {
        active_key = id;
    }
}

std::string Stats::getCurrentTitle() const
{
    // Return the title of the currently active graph
    return titles.at(active_key);
}

void Stats::next()
{
    // Cycle to the next graph ID
    active_key = (active_key + 1) % titles.size();
}

void Stats::previous()
{
    // Move to the previous graph ID, wrapping around if needed
    active_key--;
    if (active_key < 0) {
        active_key = titles.size() - 1;
    }
}

void Stats::focusOn(const std::string graph_title)
{
    // Search for the graph title and activate it if found
    for (const auto& title : titles) {
        if (title.second == graph_title) {
            setActive(title.first);
            graphs[title.first]->reset(); // Reset the graph's data
            return;
        }
    }
}

void Stats::reset()
{
    // Reset all graphs in the map
    for (auto& graph : graphs) {
        if (graph.second != nullptr) {
            graph.second->reset();
        }
    }
}

void Stats::addGraph(
    int id,
    const std::string &title,
    const std::vector<std::string> &series,
    double min,
    double max,
    const Vec2d &size)
{

    // Create a new Graph and assign it to the map
    graphs[id].reset(new Graph(series, size, min, max)); // reset method of a unique_ptr
    titles[id] = title;
    setActive(id);
}

void Stats::update(sf::Time deltaEpoch)
{
    refresh_rate_counter += deltaEpoch;

    if (refresh_rate_counter.asSeconds() >= getAppConfig().stats_refresh_rate) {
        // Fetch new data for the active graph
        std::unordered_map<std::string, double> new_data;
        new_data = getAppEnv().fetchData(titles[active_key]);

        graphs[active_key]->updateData(deltaEpoch, new_data);

        refresh_rate_counter = sf::Time::Zero;
    }
}




