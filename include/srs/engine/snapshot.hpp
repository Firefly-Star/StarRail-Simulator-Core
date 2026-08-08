#pragma once

#include "srs/state/game_state.hpp"

#include <string>
#include <vector>

namespace srs {

// 通讯边界类型：由内部 GameState 投影得到的渲染快照，仅用于 core <-> Python 通讯。
// 不参与战斗逻辑，逻辑状态一律走 srs::GameState。
struct TickSnapshot {
    struct QueueItem {
        // 行动队列中展示的剩余 AV。
        double current_av;

        // 该队列行对应的角色 id。
        std::string char_id;

        // 该队列行的显示名。
        std::string name;

        // 该角色展示用速度。
        int speed;

        // 是否为敌方队列行。
        bool is_enemy;

        // 当前能量，主要用于我方角色展示。
        int energy;

        // 最大能量，主要用于我方角色展示。
        int max_energy;

        // 编队/显示位置。
        int position;

        QueueItem() : current_av(0.0), speed(0), is_enemy(false), energy(0), max_energy(0), position(0) {}
    };

    // snapshot 对应的 tick 下标。
    int tick = 0;

    // 显示/逻辑回合计数。
    int turn = 0;

    // 当前 phase 名称。
    std::string phase;

    // 当前 phase 剩余 tick 数。
    int phase_remaining_ticks = 0;

    // 展示给用户的状态消息。
    std::string message;

    // 展示给用户的错误消息。
    std::string error;

    // 战斗日志行。
    std::vector<std::string> log;

    // 渲染用行动队列行。
    std::vector<QueueItem> action_queue;

    // 渲染用即时行动队列标签。
    std::vector<std::string> top_queue;

    // 当前全队共享战技点。
    int skill_points = 3;

    // 当前全队共享战技点上限。
    int max_skill_points = 5;

    // 当前行动角色 id。空字符串表示没有当前角色。
    std::string current_actor_id;

    // 当前行动角色显示名。
    std::string current_actor_name;

    // 当前行动角色速度。
    int current_actor_speed = 0;

    // 当前行动角色能量。
    int current_actor_energy = 0;

    // 当前行动角色最大能量。
    int current_actor_max_energy = 0;

    // 当前行动角色编队/显示位置。
    int current_actor_position = 0;

    // 当前行动角色是否为敌方。
    bool is_enemy_turn = false;
};

// 将内部战斗状态投影为通讯快照。快照只承载渲染所需字段，
// 引擎内部一律持有 GameState，不在引擎内直接保存快照。
TickSnapshot make_snapshot(const GameState& game_state);

}  // namespace srs
