#pragma once

#include <pybind11/pytypes.h>

#include <string>
#include <utility>
#include <vector>

namespace srs::state {

struct GameState {
    int tick;
    std::string phase;
    int phase_remaining_ticks;
    int turn = 0;
    std::string current_actor_id = "";
    pybind11::object current_action = pybind11::none();
    std::string message = "";
    std::string error = "";
    double error_time = 0.0;
    std::vector<std::string> log = {};
    pybind11::object action_queue = pybind11::none();
    pybind11::object action_top = pybind11::none();
    pybind11::object resources = pybind11::none();
    std::string suspended_normal_actor_id = "";
    pybind11::object last_result = pybind11::none();
    pybind11::object active_actor = pybind11::none();

    GameState(
        int tick,
        std::string phase,
        int phase_remaining_ticks,
        int turn = 0,
        std::string current_actor_id = "",
        pybind11::object current_action = pybind11::none(),
        std::string message = "",
        std::string error = "",
        double error_time = 0.0,
        std::vector<std::string> log = {},
        pybind11::object action_queue = pybind11::none(),
        pybind11::object action_top = pybind11::none(),
        pybind11::object resources = pybind11::none(),
        std::string suspended_normal_actor_id = "",
        pybind11::object last_result = pybind11::none(),
        pybind11::object active_actor = pybind11::none()
    )
        : tick(tick),
          phase(std::move(phase)),
          phase_remaining_ticks(phase_remaining_ticks),
          turn(turn),
          current_actor_id(std::move(current_actor_id)),
          current_action(std::move(current_action)),
          message(std::move(message)),
          error(std::move(error)),
          error_time(error_time),
          log(std::move(log)),
          action_queue(std::move(action_queue)),
          action_top(std::move(action_top)),
          resources(std::move(resources)),
          suspended_normal_actor_id(std::move(suspended_normal_actor_id)),
          last_result(std::move(last_result)),
          active_actor(std::move(active_actor)) {}
};

}  // namespace srs::state
