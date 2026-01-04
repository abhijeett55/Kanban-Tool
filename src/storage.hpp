#pragma once
#include "kanban.hpp"
#include <vector>
#include <string>

struct Task {
    int id;
    std::string title;
    State state;
};

class Storage {
public:
    explicit Storage(const std::string& path);

    std::vector<Task> load();
    void save(const std::vector<Task>& tasks);

private:
    std::string path;
};
