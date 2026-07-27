#pragma once

#include <pybind11/pybind11.h>

namespace py = pybind11;

void bind_current_action_state(py::module_& module);
void bind_action_top_state(py::module_& module);
void bind_resources_state(py::module_& module);
void bind_action_queue_state(py::module_& module);
void bind_game_state(py::module_& module);
