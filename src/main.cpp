#include <iostream>
#include <vector>
#include <algorithm>
#include "storage.hpp"

const char* DEFAULT_FILE = "kanban.json";

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout <<
            "kanban-tool 0.1.0\n"
            "A command line kanban board in C++\n\n"
            "USAGE:\n"
            "  kanban-tool <command> [args]\n\n"
            "COMMANDS:\n"
            "  add <title>\n"
            "  delete <id>\n"
            "  show\n"
            "  promote <id>\n"
            "  regress <id>\n";
        return 0;
    }

    Storage storage(DEFAULT_FILE);
    auto tasks = storage.load();
    std::string cmd = argv[1];

    if (cmd == "add") {
        if (argc < 3) {
            std::cout << "Title required\n";
            return 1;
        }

        std::string title = argv[2];
        int nextId = tasks.empty() ? 1 : tasks.back().id + 1;

        tasks.push_back({ nextId, title, State::TODO });
        storage.save(tasks);

        std::cout << "Added task #" << nextId << "\n";
    }

    else if (cmd == "show") {
        for (auto& t : tasks) {
            std::cout << t.id << " | "
                      << stateToString(t.state) << " | "
                      << t.title << "\n";
        }
    }

    else if (cmd == "delete") {
        int id = std::stoi(argv[2]);
        tasks.erase(
            std::remove_if(tasks.begin(), tasks.end(),
                           [&](auto& t){ return t.id == id; }),
            tasks.end()
        );
        storage.save(tasks);
    }

    else if (cmd == "promote") {
        int id = std::stoi(argv[2]);
        for (auto& t : tasks) {
            if (t.id == id) {
                if (t.state == State::TODO) t.state = State::IN_PROGRESS;
                else if (t.state == State::IN_PROGRESS) t.state = State::DONE;
            }
        }
        storage.save(tasks);
    }

    else if (cmd == "regress") {
        int id = std::stoi(argv[2]);
        for (auto& t : tasks) {
            if (t.id == id) {
                if (t.state == State::DONE) t.state = State::IN_PROGRESS;
                else if (t.state == State::IN_PROGRESS) t.state = State::TODO;
            }
        }
        storage.save(tasks);
    }

    return 0;
}
