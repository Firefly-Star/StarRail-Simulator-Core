#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "bindings.hpp"
#include "srs/state/action_queue_state.hpp"
#include "srs/state/action_state.hpp"
#include "srs/state/action_top_state.hpp"
#include "srs/state/game_state.hpp"

void bind_game_state(py::module_& module) {
    using srs::GameState;
    using srs::ActionQueueState;
    using srs::ActionTopState;
    using srs::ResourcesState;

    py::class_<GameState>(module, "GameState")
        .def(
            py::init<
                int,
                std::string,
                int,
                int,
                std::string,
                py::object,
                std::string,
                std::string,
                double,
                std::vector<std::string>,
                ActionQueueState,
                ActionTopState,
                ResourcesState,
                std::string,
                py::object,
                py::object
            >(),
            py::arg("tick"),
            py::arg("phase"),
            py::arg("phase_remaining_ticks"),
            py::arg("turn") = 0,
            py::arg("current_actor_id") = "",
            py::arg("current_action") = py::none(),
            py::arg("message") = "",
            py::arg("error") = "",
            py::arg("error_time") = 0.0,
            py::arg("log") = std::vector<std::string>{},
            py::arg("action_queue") = ActionQueueState{},
            py::arg("action_top") = ActionTopState{},
            py::arg("resources") = ResourcesState{},
            py::arg("suspended_normal_actor_id") = "",
            py::arg("last_result") = py::none(),
            py::arg("active_actor") = py::none()
        )
        .def_readwrite("tick", &GameState::tick)
        .def_readwrite("phase", &GameState::phase)
        .def_readwrite("phase_remaining_ticks", &GameState::phase_remaining_ticks)
        .def_readwrite("turn", &GameState::turn)
        .def_readwrite("current_actor_id", &GameState::current_actor_id)
        .def_readwrite("current_action", &GameState::current_action)
        .def_readwrite("message", &GameState::message)
        .def_readwrite("error", &GameState::error)
        .def_readwrite("error_time", &GameState::error_time)
        .def_readwrite("log", &GameState::log)
        .def_readwrite("action_queue", &GameState::action_queue)
        .def_readwrite("action_top", &GameState::action_top)
        .def_readwrite("resources", &GameState::resources)
        .def_readwrite("suspended_normal_actor_id", &GameState::suspended_normal_actor_id)
        .def_readwrite("last_result", &GameState::last_result)
        .def_readwrite("active_actor", &GameState::active_actor);
}
