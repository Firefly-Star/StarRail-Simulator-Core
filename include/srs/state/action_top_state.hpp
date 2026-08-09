#pragma once

#include <string>
#include <utility>
#include <vector>

namespace srs {

constexpr int TOP_PRIORITY_FOLLOW_UP = 0;
constexpr int TOP_PRIORITY_EXTRA_TURN = 1;
constexpr int TOP_PRIORITY_ULTIMATE = 1;
constexpr int TOP_PRIORITY_NORMAL = 2;

struct ActionTopEntryState {
    // 执行优先级，数值越小优先级越高。
    int priority;

    // 同优先级条目的 FIFO 并列裁决序号。
    int seq;

    // 该即时行动条目的所属角色。
    std::string char_id;

    // 行动类别，例如 normal、ultimate、follow_up、extra_turn。
    std::string action_type;

    // 该条目被派发时要进入的 phase。空字符串表示由调度逻辑决定。
    std::string phase = "";

    // 该即时行动绑定的技能 id。空字符串表示使用 action_type 的默认行动。
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
    // 即时行动条目。这里只存数据，入队、出队和排序由调度逻辑负责。
    std::vector<ActionTopEntryState> entries;

    ActionTopState() = default;
    explicit ActionTopState(std::vector<ActionTopEntryState> entries)
        : entries(std::move(entries)) {}
};

}  // namespace srs
