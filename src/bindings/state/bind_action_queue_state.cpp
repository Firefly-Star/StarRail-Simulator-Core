#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "bindings.hpp"
#include "srs/state/action_queue_state.hpp"

void bind_action_queue_state(py::module_& module) {
    using srs::state::ActionQueueItemState;

    py::class_<ActionQueueItemState>(module, "ActionQueueItemState")
        .def(
            py::init<std::string, double, int, bool, std::string, int, int, int, int>(),
            py::arg("char_id"),
            py::arg("current_av"),
            py::arg("av_epoch"),
            py::arg("is_enemy"),
            py::arg("name") = "",
            py::arg("speed") = 0,
            py::arg("energy") = 0,
            py::arg("max_energy") = 0,
            py::arg("position") = 0
        )
        .def_readwrite("char_id", &ActionQueueItemState::char_id)
        .def_readwrite("current_av", &ActionQueueItemState::current_av)
        .def_readwrite("av_epoch", &ActionQueueItemState::av_epoch)
        .def_readwrite("is_enemy", &ActionQueueItemState::is_enemy)
        .def_readwrite("name", &ActionQueueItemState::name)
        .def_readwrite("speed", &ActionQueueItemState::speed)
        .def_readwrite("energy", &ActionQueueItemState::energy)
        .def_readwrite("max_energy", &ActionQueueItemState::max_energy)
        .def_readwrite("position", &ActionQueueItemState::position);
}
