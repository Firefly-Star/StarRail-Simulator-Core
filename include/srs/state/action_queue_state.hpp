#pragma once

#include <string>
#include <utility>
#include <vector>

namespace srs {

struct ActionQueueItemState {
    std::string char_id;
    double current_av;
    int av_epoch;
    bool is_enemy;
    std::string name = "";
    int speed = 0;
    int energy = 0;
    int max_energy = 0;
    int position = 0;

    ActionQueueItemState(
        std::string char_id,
        double current_av,
        int av_epoch,
        bool is_enemy,
        std::string name = "",
        int speed = 0,
        int energy = 0,
        int max_energy = 0,
        int position = 0
    )
        : char_id(std::move(char_id)),
          current_av(current_av),
          av_epoch(av_epoch),
          is_enemy(is_enemy),
          name(std::move(name)),
          speed(speed),
          energy(energy),
          max_energy(max_energy),
          position(position) {}
};

struct ActionQueueState {
    std::vector<ActionQueueItemState> items;

    ActionQueueState() = default;
    explicit ActionQueueState(std::vector<ActionQueueItemState> items)
        : items(std::move(items)) {}
};

}  // namespace srs
