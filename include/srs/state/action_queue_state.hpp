#pragma once

#include <string>
#include <utility>
#include <vector>

namespace srs {

struct ActionQueueItemState {
    // 角色稳定 id，供规则和 snapshot 引用。
    std::string char_id;

    // 该角色到达行动队列头部前剩余的行动值 AV。
    double current_av;

    // 同 AV 排序的并列裁决标记。这里只保存状态，不保存下一个计数器。
    int av_epoch;

    // 是否为敌方角色。false 表示我方角色。
    bool is_enemy;

    // 显示名，缓存给 snapshot/render 使用。
    std::string name = "";

    // 角色速度，用于 AV 计算。
    int speed = 0;

    // 当前能量值，用于判断终结技是否可用。
    int energy = 0;

    // 能量上限，也就是该角色终结技的启动阈值。
    int max_energy = 0;

    // 编队/显示位置，用于保持 snapshot 中队伍区域的稳定顺序。
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
    // 已排序的行动队列项。排序规则属于调度逻辑，这里只存状态。
    std::vector<ActionQueueItemState> items;

    ActionQueueState() = default;
    explicit ActionQueueState(std::vector<ActionQueueItemState> items)
        : items(std::move(items)) {}
};

}  // namespace srs
