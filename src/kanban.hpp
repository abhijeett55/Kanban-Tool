#pragma once
#include <string>

enum class State {
    TODO,
    IN_PROGRESS,
    DONE
};

inline std::string stateToString(State s) {
    switch (s) {
        case State::TODO: return "TODO";
        case State::IN_PROGRESS: return "IN_PROGRESS";
        case State::DONE: return "DONE";
    }
    return "TODO";
}

inline State stringToState(const std::string& s) {
    if (s == "IN_PROGRESS") return State::IN_PROGRESS;
    if (s == "DONE") return State::DONE;
    return State::TODO;
}
