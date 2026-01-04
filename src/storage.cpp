#include "storage.hpp"
#include "../third_party/json.hpp" 
#include <fstream>
#include <iostream>

using json = nlohmann::json;

Storage::Storage(const std::string& path) : path(path) {}

std::vector<Task> Storage::load() {
    std::ifstream in(path);
    if (!in.is_open()) return {};

    json j;
    in >> j;

    std::vector<Task> tasks;
    for (auto& item : j) {
        tasks.push_back({
            item["id"],
            item["title"],
            stringToState(item["state"])
        });
    }
    return tasks;
}

void Storage::save(const std::vector<Task>& tasks) {
    json j = json::array();
    for (auto& t : tasks) {
        j.push_back({
            {"id", t.id},
            {"title", t.title},
            {"state", stateToString(t.state)}
        });
    }

    std::ofstream out(path);
    out << j.dump(2);
}
