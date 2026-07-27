#include <pybind11/pybind11.h>

#include "bindings.hpp"
#include "srs/logic/advance.hpp"

void bind_logic_advance(py::module_& module) {
    module.def("do_advance", &srs::do_advance, py::arg("game_state"));
}
