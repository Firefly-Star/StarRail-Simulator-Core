#pragma once

#include <chrono>
#include <string>
#include <vector>

#include "srs/engine/snapshot.hpp"
#include "srs/state/game_state.hpp"

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

class BattleEngine {
public:
    void init(const BattleConfig& cfg);

    void begin_tick_timing();
    void exchange_state_buffers();
    // 仅用于 core <-> Python 通讯：由当前 GameState 投影得到。
    TickSnapshot get_snapshot() const;
    // TODO(mock): 当前只生成 mock GameState，需替换为真实结算。
    void compute_next(const std::vector<InputEvent>& inputs);
    void wait_until_tick_end() const;

    bool is_over() const;

private:
    // TODO(mock): 生成假 GameState，真实引擎接入后删除。
    GameState make_mock_gamestate(int tick) const;

    // —— 随 tick 变化的状态变量 ——
    bool over = false;
    int current_tick = -1;
    int next_tick = 0;
    GameState current_gamestate;
    GameState next_gamestate;
    std::chrono::steady_clock::time_point tick_deadline;
    bool tick_timing_started = false;

    // —— 基本不会变化的产品配置 ——
    BattleConfig config;
    double tick_duration_seconds = 0.05;

    // —— mock 阶段临时保留的变量 ——
    // 当前无；mock 逻辑集中在 make_mock_gamestate。
};

}  // namespace srs
