#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "srs/state/current_action_state.hpp"

namespace py = pybind11;

PYBIND11_MODULE(starrail_cpp_core, m) {
    using srs::state::CurrentActionState;

    py::class_<CurrentActionState>(m, "CurrentActionState")
        .def(
            py::init<
                std::string,
                std::string,
                std::string,
                std::string,
                int,
                std::string,
                std::vector<std::string>,
                bool,
                bool
            >(),
            py::arg("action_type"),
            py::arg("actor_id"),
            py::arg("skill_id") = "",
            py::arg("selected_target_id") = "",
            py::arg("selected_target_index") = -1,
            py::arg("selected_target_name") = "",
            py::arg("valid_main_targets") = std::vector<std::string>{},
            py::arg("needs_target") = true,
            py::arg("needs_confirm") = true
        )
        .def_readwrite("action_type", &CurrentActionState::action_type)
        .def_readwrite("actor_id", &CurrentActionState::actor_id)
        .def_readwrite("skill_id", &CurrentActionState::skill_id)
        .def_readwrite("selected_target_id", &CurrentActionState::selected_target_id)
        .def_readwrite("selected_target_index", &CurrentActionState::selected_target_index)
        .def_readwrite("selected_target_name", &CurrentActionState::selected_target_name)
        .def_readwrite("valid_main_targets", &CurrentActionState::valid_main_targets)
        .def_readwrite("needs_target", &CurrentActionState::needs_target)
        .def_readwrite("needs_confirm", &CurrentActionState::needs_confirm);
}
