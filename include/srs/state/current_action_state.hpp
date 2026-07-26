#pragma once

#include <string>
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
};

}  // namespace srs::state
