#include "srs/engine/battle_engine.hpp"

#include <algorithm>

namespace srs {

void BattleEngine::init(const BattleConfig& config) {
    config_ = config;
    tick_count_ = 0;
    over_ = false;
}

TickSnapshot BattleEngine::tick(const std::vector<InputEvent>& inputs) {
    TickSnapshot snap;
    snap.tick = tick_count_++;
    snap.turn = 1;
    snap.phase = "normal_prepare";
    snap.phase_remaining_ticks = 3;
    snap.message = "希儿 的回合 — 选择指令";
    snap.error = "";
    snap.log = {"希儿 · 普攻 → 银鬃尉官"};
    snap.skill_points = 3;
    snap.max_skill_points = 5;

    TickSnapshot::QueueItem seele_item;
    seele_item.current_av = 10.0;
    seele_item.char_id = "seele";
    seele_item.name = "希儿";
    seele_item.speed = 115;
    seele_item.is_enemy = false;
    seele_item.energy = 120;
    seele_item.max_energy = 120;
    seele_item.position = 0;
    snap.action_queue.push_back(seele_item);

    TickSnapshot::QueueItem enemy_item;
    enemy_item.current_av = 20.0;
    enemy_item.char_id = "enemy1";
    enemy_item.name = "银鬃尉官";
    enemy_item.speed = 90;
    enemy_item.is_enemy = true;
    enemy_item.energy = 0;
    enemy_item.max_energy = 0;
    enemy_item.position = 1;
    snap.action_queue.push_back(enemy_item);

    snap.top_queue.push_back("[普通] 希儿");

    snap.current_actor_id = "seele";
    snap.current_actor_name = "希儿";
    snap.current_actor_speed = 115;
    snap.current_actor_energy = 120;
    snap.current_actor_max_energy = 120;
    snap.current_actor_position = 0;
    snap.is_enemy_turn = false;

    if (tick_count_ > 10) {
        over_ = true;
    }

    return snap;
}

bool BattleEngine::is_over() const {
    return over_;
}

}  // namespace srs
