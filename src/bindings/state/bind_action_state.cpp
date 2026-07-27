#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "bindings.hpp"
#include "srs/state/action_state.hpp"

void bind_current_action_state(py::module_& module) {
    using srs::CurrentActionState;

    py::class_<CurrentActionState>(module, "CurrentActionState")
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

void bind_resources_state(py::module_& module) {
    using srs::ResourcesState;

    py::class_<ResourcesState>(module, "ResourcesState")
        .def(py::init<int, int>(), py::arg("skill_points") = 3, py::arg("max_skill_points") = 5)
        .def_readwrite("skill_points", &ResourcesState::skill_points)
        .def_readwrite("max_skill_points", &ResourcesState::max_skill_points);
}
