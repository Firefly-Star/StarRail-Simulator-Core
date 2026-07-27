#pragma once

#include <string>
#include <utility>
#include <vector>

namespace srs {

constexpr int TOP_PRIORITY_FOLLOW_UP = 0;
constexpr int TOP_PRIORITY_EXTRA_TURN = 1;
constexpr int TOP_PRIORITY_ULTIMATE = 2;
constexpr int TOP_PRIORITY_NORMAL = 3;

struct ActionTopEntryState {
    int priority;
    int seq;
    std::string char_id;
    std::string action_type;
    std::string phase = "";
    std::string skill_id = "";

    ActionTopEntryState(
        int priority,
        int seq,
        std::string char_id,
        std::string action_type,
        std::string phase = "",
        std::string skill_id = ""
    )
        : priority(priority),
          seq(seq),
          char_id(std::move(char_id)),
          action_type(std::move(action_type)),
          phase(std::move(phase)),
          skill_id(std::move(skill_id)) {}
};

struct ActionTopState {
    std::vector<ActionTopEntryState> entries;

    ActionTopState() = default;
    explicit ActionTopState(std::vector<ActionTopEntryState> entries)
        : entries(std::move(entries)) {}
};

}  // namespace srs
