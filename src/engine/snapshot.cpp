#include "srs/engine/snapshot.hpp"

#include <string>
#include <unordered_map>

namespace srs {

namespace {

const std::unordered_map<std::string, std::string>& action_type_labels() {
    static const std::unordered_map<std::string, std::string> labels = {
        {"normal", "普通"},
        {"ultimate", "终结技"},
        {"follow_up", "追加攻击"},
        {"extra_turn", "额外回合"},
    };
    return labels;
}

std::string char_name(const GameState& game_state, const std::string& char_id) {
    for (const auto& item : game_state.action_queue.items) {
        if (item && item->char_id == char_id) {
            return item->name.empty() ? item->char_id : item->name;
        }
    }
    return char_id;
}

}  // namespace

TickSnapshot make_snapshot(const GameState& game_state) {
    TickSnapshot snap;

    snap.tick = game_state.tick;
    snap.turn = game_state.turn;
    snap.phase = game_state.phase;
    snap.phase_remaining_ticks = game_state.phase_remaining_ticks;
    snap.message = game_state.message;
    snap.error = game_state.error;
    snap.log = game_state.log;
    snap.skill_points = game_state.resources.skill_points;
    snap.max_skill_points = game_state.resources.max_skill_points;
    snap.current_actor_id = game_state.current_actor_id;

    for (const auto& item : game_state.action_queue.items) {
        if (!item) {
            continue;
        }
        TickSnapshot::QueueItem qi;
        qi.current_av = item->current_av;
        qi.char_id = item->char_id;
        qi.name = item->name;
        qi.speed = static_cast<int>(item->speed());
        qi.is_enemy = item->is_enemy;
        qi.energy = item->energy;
        qi.max_energy = item->max_energy;
        qi.position = item->position;
        snap.action_queue.push_back(qi);
    }

    for (const auto& item : game_state.action_queue.items) {
        if (item && item->char_id == game_state.current_actor_id) {
            snap.current_actor_name = item->name;
            snap.current_actor_speed = static_cast<int>(item->speed());
            snap.current_actor_energy = item->energy;
            snap.current_actor_max_energy = item->max_energy;
            snap.current_actor_position = item->position;
            snap.is_enemy_turn = item->is_enemy;
            break;
        }
    }

    for (const auto& entry : game_state.action_top.entries) {
        const auto& labels = action_type_labels();
        auto it = labels.find(entry.action_type);
        std::string label = (it != labels.end()) ? it->second : entry.action_type;
        snap.top_queue.push_back("[" + label + "] " + char_name(game_state, entry.char_id));
    }

    return snap;
}

}  // namespace srs
