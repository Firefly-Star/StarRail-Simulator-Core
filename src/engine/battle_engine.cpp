#include "srs/engine/battle_engine.hpp"

#include <algorithm>
#include <chrono>
#include <memory>
#include <thread>

namespace srs {

void BattleEngine::init(const BattleConfig& cfg) {
    config = cfg;
    over = false;
    current_tick = -1;
    next_tick = 0;
    current_gamestate = GameState(0, "", 0);
    next_gamestate = make_mock_gamestate(0);
    tick_timing_started = false;
}

void BattleEngine::begin_tick_timing() {
    tick_timing_started = true;
    auto duration = std::chrono::duration<double>(tick_duration_seconds);
    tick_deadline = std::chrono::steady_clock::now() + std::chrono::duration_cast<std::chrono::steady_clock::duration>(duration);
}

void BattleEngine::exchange_state_buffers() {
    current_gamestate = next_gamestate;
    current_tick = current_gamestate.tick;
    next_tick = current_tick + 1;

    if (current_tick >= 10) {
        over = true;
    }
}

TickSnapshot BattleEngine::get_snapshot() const {
    return make_snapshot(current_gamestate);
}

void BattleEngine::compute_next(const std::vector<InputEvent>& inputs) {
    (void)inputs;
    if (over) {
        return;
    }
    next_gamestate = make_mock_gamestate(next_tick);
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

GameState BattleEngine::make_mock_gamestate(int tick) const {
    GameState gs(tick, "normal_prepare", 3, 1, "seele");
    gs.message = "希儿 的回合 — 选择指令";
    gs.error = "";
    gs.log = {"希儿 · 普攻 → 银鬃尉官"};
    gs.resources = ResourcesState(3, 5);

    auto seele = std::make_unique<Character>();
    seele->id = 0;
    seele->char_id = "seele";
    seele->name = "希儿";
    seele->speed_ = 115;
    seele->current_av = 10.0;
    seele->is_enemy = false;
    seele->energy = 120;
    seele->max_energy = 120;
    seele->position = 0;

    auto enemy = std::make_unique<Enemy>();
    enemy->id = 1;
    enemy->char_id = "enemy1";
    enemy->name = "银鬃尉官";
    enemy->speed_ = 90;
    enemy->current_av = 20.0;
    enemy->is_enemy = true;
    enemy->position = 1;

    std::vector<std::unique_ptr<Actor>> items;
    items.push_back(std::move(seele));
    items.push_back(std::move(enemy));
    gs.action_queue.items = std::move(items);

    ActionTopEntryState top(TOP_PRIORITY_NORMAL, 0, "seele", "normal");
    gs.action_top.entries = {top};

    return gs;
}

bool BattleEngine::is_over() const {
    return over;
}

}  // namespace srs
