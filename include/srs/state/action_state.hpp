#pragma once

#include <string>
#include <utility>
#include <vector>

namespace srs {

struct CurrentActionState {
    // 当前正在准备或结算的行动类别，例如 normal、skill、ultimate。
    std::string action_type;

    // 当前行动的所属角色。
    std::string actor_id;

    // 当前行动选择的技能 id。空字符串表示尚未选择技能。
    std::string skill_id = "";

    // 已选择的主目标 id。空字符串表示尚未选择目标。
    std::string selected_target_id = "";

    // 已选目标在 valid_main_targets 中的下标。-1 表示尚未选择目标。
    int selected_target_index = -1;

    // 已选目标的显示名，缓存给 snapshot/render 使用。
    std::string selected_target_name = "";

    // 当前行动可选的合法主目标 id 列表，顺序用于目标选择。
    std::vector<std::string> valid_main_targets = {};

    // 当前行动是否需要进入目标选择阶段。
    bool needs_target = true;

    // 当前行动在结算前是否需要玩家显式确认。
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
    // 当前全队共享战技点数量。
    int skill_points;

    // 当前全队共享战技点上限。
    int max_skill_points;

    ResourcesState(int skill_points = 3, int max_skill_points = 5)
        : skill_points(skill_points),
          max_skill_points(max_skill_points) {}
};

}  // namespace srs
