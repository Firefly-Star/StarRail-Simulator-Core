#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "bindings.hpp"
#include "srs/engine/battle_engine.hpp"

void bind_engine(py::module_& module) {
    using srs::InputEvent;
    using srs::BattleConfig;
    using srs::TickSnapshot;
    using srs::BattleEngine;

    py::class_<InputEvent>(module, "InputEvent")
        .def(py::init<>())
        .def(py::init<char, double>(), py::arg("key"), py::arg("timestamp") = 0.0)
        .def_readwrite("key", &InputEvent::key)
        .def_readwrite("timestamp", &InputEvent::timestamp);

    py::class_<BattleConfig::Character>(module, "BattleCharacter")
        .def(py::init<>())
        .def(py::init<std::string, std::string, int, int, bool, int>(),
             py::arg("id"), py::arg("name"), py::arg("speed"),
             py::arg("max_energy"), py::arg("is_enemy"), py::arg("position"))
        .def_readwrite("id", &BattleConfig::Character::id)
        .def_readwrite("name", &BattleConfig::Character::name)
        .def_readwrite("speed", &BattleConfig::Character::speed)
        .def_readwrite("max_energy", &BattleConfig::Character::max_energy)
        .def_readwrite("is_enemy", &BattleConfig::Character::is_enemy)
        .def_readwrite("position", &BattleConfig::Character::position);

    py::class_<BattleConfig>(module, "BattleConfig")
        .def(py::init<>())
        .def_readwrite("characters", &BattleConfig::characters);

    py::class_<TickSnapshot::QueueItem>(module, "SnapshotQueueItem")
        .def(py::init<>())
        .def_readwrite("current_av", &TickSnapshot::QueueItem::current_av)
        .def_readwrite("char_id", &TickSnapshot::QueueItem::char_id)
        .def_readwrite("name", &TickSnapshot::QueueItem::name)
        .def_readwrite("speed", &TickSnapshot::QueueItem::speed)
        .def_readwrite("is_enemy", &TickSnapshot::QueueItem::is_enemy)
        .def_readwrite("energy", &TickSnapshot::QueueItem::energy)
        .def_readwrite("max_energy", &TickSnapshot::QueueItem::max_energy)
        .def_readwrite("position", &TickSnapshot::QueueItem::position);

    py::class_<TickSnapshot>(module, "TickSnapshot")
        .def(py::init<>())
        .def_readwrite("tick", &TickSnapshot::tick)
        .def_readwrite("turn", &TickSnapshot::turn)
        .def_readwrite("phase", &TickSnapshot::phase)
        .def_readwrite("phase_remaining_ticks", &TickSnapshot::phase_remaining_ticks)
        .def_readwrite("message", &TickSnapshot::message)
        .def_readwrite("error", &TickSnapshot::error)
        .def_readwrite("log", &TickSnapshot::log)
        .def_readwrite("action_queue", &TickSnapshot::action_queue)
        .def_readwrite("top_queue", &TickSnapshot::top_queue)
        .def_readwrite("skill_points", &TickSnapshot::skill_points)
        .def_readwrite("max_skill_points", &TickSnapshot::max_skill_points)
        .def_readwrite("current_actor_id", &TickSnapshot::current_actor_id)
        .def_readwrite("current_actor_name", &TickSnapshot::current_actor_name)
        .def_readwrite("current_actor_speed", &TickSnapshot::current_actor_speed)
        .def_readwrite("current_actor_energy", &TickSnapshot::current_actor_energy)
        .def_readwrite("current_actor_max_energy", &TickSnapshot::current_actor_max_energy)
        .def_readwrite("current_actor_position", &TickSnapshot::current_actor_position)
        .def_readwrite("is_enemy_turn", &TickSnapshot::is_enemy_turn);

    py::class_<BattleEngine>(module, "BattleEngine")
        .def(py::init<>())
        .def("init", &BattleEngine::init, py::arg("config"))
        .def("tick", &BattleEngine::tick, py::arg("inputs"))
        .def("is_over", &BattleEngine::is_over);
}
