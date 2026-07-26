#pragma once

#include <pybind11/pybind11.h>

namespace py = pybind11;

void bind_current_action_state(py::module_& module);
