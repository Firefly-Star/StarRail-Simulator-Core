#pragma once

#include "srs/state/actor.hpp"

#include <memory>
#include <utility>
#include <vector>

namespace srs {

struct ActionQueueState {
    std::vector<Actor> items;
};

}  // namespace srs
