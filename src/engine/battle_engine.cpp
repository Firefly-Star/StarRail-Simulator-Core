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

    ActionQueueItemState seele("seele", 10.0, 0, false, "希儿", 115, 120, 120, 0);
    ActionQueueItemState enemy("enemy1", 20.0, 0, true, "银鬃尉官", 90, 0, 0, 1);
    gs.action_queue.items = {seele, enemy};

    ActionTopEntryState top(TOP_PRIORITY_NORMAL, 0, "seele", "normal");
    gs.action_top.entries = {top};

    return gs;
}

bool BattleEngine::is_over() const {
    return over;
}

}  // namespace srs
