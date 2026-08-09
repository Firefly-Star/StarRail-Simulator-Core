#include "srs/logic/advance.hpp"

#include <cmath>
#include <memory>
#include <optional>

#include <utility>
#include <vector>

#include "srs/state/action_queue_state.hpp"

namespace srs {

GameState do_advance(const GameState& game_state) {
    if (game_state.action_queue.items.empty()) {
        return game_state;
    }

    auto items = clone_actors(game_state.action_queue.items);
    const double head_av = items.front()->current_av;
    if (head_av > 0.0) {
        for (auto& item : items) {
            item->current_av = std::round((item->current_av - head_av) * 100.0) / 100.0;
        }
    }

    std::unique_ptr<Actor> actor_item = std::move(items.front());
    actor_item->current_av = 0.0;
    items.erase(items.begin());

    return GameState(
        game_state.tick,
        "",
        0,
        game_state.turn + 1,
        actor_item->char_id,
        std::nullopt,
        game_state.message,
        game_state.error,
        game_state.error_time,
        game_state.log,
        ActionQueueState{std::move(items)},
        game_state.action_top,
        game_state.resources,
        game_state.suspended_normal_actor_id,
        game_state.last_result,
        std::move(actor_item)
    );
}

}  // namespace srs
