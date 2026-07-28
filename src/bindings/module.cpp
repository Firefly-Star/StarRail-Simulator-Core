#include <pybind11/pybind11.h>
#include "bindings.hpp"

namespace py = pybind11;

PYBIND11_MODULE(starrail_cpp_core, m) {
    bind_engine(m);
}
