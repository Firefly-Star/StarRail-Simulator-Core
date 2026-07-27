#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "bindings.hpp"
#include "srs/state/action_top_state.hpp"

void bind_action_top_state(py::module_& module) {
    using srs::ActionTopEntryState;
    using srs::ActionTopState;

    module.attr("TOP_PRIORITY_FOLLOW_UP") = srs::TOP_PRIORITY_FOLLOW_UP;
    module.attr("TOP_PRIORITY_EXTRA_TURN") = srs::TOP_PRIORITY_EXTRA_TURN;
    module.attr("TOP_PRIORITY_ULTIMATE") = srs::TOP_PRIORITY_ULTIMATE;
    module.attr("TOP_PRIORITY_NORMAL") = srs::TOP_PRIORITY_NORMAL;

    py::class_<ActionTopEntryState>(module, "ActionTopEntryState")
        .def(
            py::init<int, int, std::string, std::string, std::string, std::string>(),
            py::arg("priority"),
            py::arg("seq"),
            py::arg("char_id"),
            py::arg("action_type"),
            py::arg("phase") = "",
            py::arg("skill_id") = ""
        )
        .def_readwrite("priority", &ActionTopEntryState::priority)
        .def_readwrite("seq", &ActionTopEntryState::seq)
        .def_readwrite("char_id", &ActionTopEntryState::char_id)
        .def_readwrite("action_type", &ActionTopEntryState::action_type)
        .def_readwrite("phase", &ActionTopEntryState::phase)
        .def_readwrite("skill_id", &ActionTopEntryState::skill_id);

    py::class_<ActionTopState>(module, "ActionTopState")
        .def(py::init<>())
        .def(py::init<std::vector<ActionTopEntryState>>(),
             py::arg("entries") = std::vector<ActionTopEntryState>{})
        .def("entries", [](const ActionTopState& s) { return s.entries; })
        .def("set_entries", [](ActionTopState& s, const std::vector<ActionTopEntryState>& v) { s.entries = v; })
        .def("__len__", [](const ActionTopState& s) { return s.entries.size(); })
        .def("empty", [](const ActionTopState& s) { return s.entries.empty(); });
}
