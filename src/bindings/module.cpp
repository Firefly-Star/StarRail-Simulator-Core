#include <pybind11/pybind11.h>
#include "bindings.hpp"

namespace py = pybind11;

PYBIND11_MODULE(starrail_cpp_core, m) {
    bind_action_queue_state(m);
    bind_current_action_state(m);
    bind_action_top_state(m);
    bind_resources_state(m);
    bind_game_state(m);
    bind_engine(m);
    bind_logic_advance(m);
}
