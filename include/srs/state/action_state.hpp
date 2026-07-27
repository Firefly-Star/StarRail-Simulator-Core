#pragma once

#include <string>
#include <utility>
#include <vector>

namespace srs::state {

struct CurrentActionState {
    std::string action_type;
    std::string actor_id;
    std::string skill_id = "";
    std::string selected_target_id = "";
    int selected_target_index = -1;
    std::string selected_target_name = "";
    std::vector<std::string> valid_main_targets = {};
    bool needs_target = true;
    bool needs_confirm = true;

    CurrentActionState(
        std::string action_type,
        std::string actor_id,
        std::string skill_id = "",
        std::string selected_target_id = "",
        int selected_target_index = -1,
        std::string selected_target_name = "",
        std::vector<std::string> valid_main_targets = {},
        bool needs_target = true,
        bool needs_confirm = true
    )
        : action_type(std::move(action_type)),
          actor_id(std::move(actor_id)),
          skill_id(std::move(skill_id)),
          selected_target_id(std::move(selected_target_id)),
          selected_target_index(selected_target_index),
          selected_target_name(std::move(selected_target_name)),
          valid_main_targets(std::move(valid_main_targets)),
          needs_target(needs_target),
          needs_confirm(needs_confirm) {}
};

struct ResourcesState {
    int skill_points;
    int max_skill_points;

    ResourcesState(int skill_points = 3, int max_skill_points = 5)
        : skill_points(skill_points),
          max_skill_points(max_skill_points) {}
};

}  // namespace srs::state
