#include "srs/engine/battle_engine.hpp"

#include <algorithm>
#include <chrono>
#include <thread>

namespace srs {

void BattleEngine::init(const BattleConfig& cfg) {
    config = cfg;
    over = false;
    current_tick = -1;
    next_tick = 0;
    current_snapshot = TickSnapshot{};
    next_snapshot = make_mock_snapshot(0);
    next_state_ready = true;
    tick_timing_started = false;
}

void BattleEngine::begin_tick_timing() {
    tick_timing_started = true;
    auto duration = std::chrono::duration<double>(tick_duration_seconds);
    tick_deadline = std::chrono::steady_clock::now() + std::chrono::duration_cast<std::chrono::steady_clock::duration>(duration);
}

void BattleEngine::exchange_state_buffers() {
    if (next_state_ready) {
        current_snapshot = next_snapshot;
    } else {
        current_snapshot = make_mock_snapshot(next_tick);
    }
    current_tick = current_snapshot.tick;
    next_tick = current_tick + 1;
    next_state_ready = false;

    if (current_tick >= 10) {
        over = true;
    }
}

TickSnapshot BattleEngine::get_snapshot() const {
    return current_snapshot;
}

void BattleEngine::compute_next(const std::vector<InputEvent>& inputs) {
    (void)inputs;
    if (over) {
        return;
    }
    next_snapshot = make_mock_snapshot(next_tick);
    next_state_ready = true;
}

void BattleEngine::wait_until_tick_end() const {
    if (!tick_timing_started) {
        return;
    }
    auto now = std::chrono::steady_clock::now();
    if (now < tick_deadline) {
        std::this_thread::sleep_until(tick_deadline);
    }
}

TickSnapshot BattleEngine::make_mock_snapshot(int tick) const {
    TickSnapshot snap;
    snap.tick = tick;
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

    return snap;
}

bool BattleEngine::is_over() const {
    return over;
}

}  // namespace srs
