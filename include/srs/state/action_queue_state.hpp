#pragma once

#include <string>
#include <utility>
#include <vector>

namespace srs::state {

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

}  // namespace srs::state
