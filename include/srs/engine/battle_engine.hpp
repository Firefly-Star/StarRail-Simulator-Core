#pragma once

#include <chrono>
#include <string>
#include <vector>

namespace srs {

struct InputEvent {
    // 产品输入层传入的原始按键。具体战斗含义由 C++ 判断。
    char key;

    // 输入层提供的按键时间戳。
    double timestamp;

    InputEvent() : key(0), timestamp(0.0) {}
    InputEvent(char key, double timestamp = 0.0) : key(key), timestamp(timestamp) {}
};

struct BattleConfig {
    struct Character {
        // 产品层选择的角色稳定 id。
        std::string id;

        // 显示名。
        std::string name;

        // 初始速度，用于初始化行动轴时序。
        int speed;

        // 最大能量，也就是终结技启动阈值。
        int max_energy;

        // 是否属于敌方。
        bool is_enemy;

        // 产品层分配的编队/显示位置。
        int position;

        Character() : speed(0), max_energy(0), is_enemy(false), position(0) {}
        Character(std::string id, std::string name, int speed, int max_energy, bool is_enemy, int position)
            : id(std::move(id)), name(std::move(name)), speed(speed), max_energy(max_energy),
              is_enemy(is_enemy), position(position) {}
    };
    std::vector<Character> characters;
};

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

class BattleEngine {
public:
    void init(const BattleConfig& cfg);

    void begin_tick_timing();
    void exchange_state_buffers();
    TickSnapshot get_snapshot() const;
    void compute_next(const std::vector<InputEvent>& inputs);
    void wait_until_tick_end() const;

    bool is_over() const;

private:
    TickSnapshot make_mock_snapshot(int tick) const;

    BattleConfig config;
    bool over = false;
    int current_tick = -1;
    int next_tick = 0;
    bool next_state_ready = false;
    TickSnapshot current_snapshot;
    TickSnapshot next_snapshot;
    std::chrono::steady_clock::time_point tick_deadline;
    bool tick_timing_started = false;
    double tick_duration_seconds = 0.05;
};

}  // namespace srs
