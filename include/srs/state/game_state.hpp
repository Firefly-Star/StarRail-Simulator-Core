#pragma once

#include "srs/state/action_queue_state.hpp"
#include "srs/state/action_state.hpp"
#include "srs/state/action_top_state.hpp"

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace srs {

struct GameState {
    // 当前已提交状态对应的 simulation tick 下标。
    int tick;

    // 当前生命周期阶段，例如 normal_prepare、normal_resolve、enemy_prepare。
    std::string phase;

    // 当前 phase 剩余 tick 数，归零后允许进入下一阶段。
    int phase_remaining_ticks;

    // 显示/逻辑回合计数。具体递增规则由 engine/规则层决定。
    int turn = 0;

    // 当前正在准备或结算行动的角色 id。空字符串表示没有当前角色。
    std::string current_actor_id = "";

    // 当前行动上下文。空 optional 表示没有正在准备/结算的行动。
    std::optional<CurrentActionState> current_action;

    // 当前 snapshot 展示给用户的状态消息。
    std::string message = "";

    // 展示给用户的错误消息。空字符串表示当前没有错误。
    std::string error = "";

    // 错误消息过期时间戳，用于 UI/debug 流程。过渡字段。
    double error_time = 0.0;

    // 按时间顺序保存的战斗日志。
    std::vector<std::string> log = {};

    // 未来普通行动的行动轴队列。
    ActionQueueState action_queue;

    // 即时行动队列，用于普通回合、终结技、追加行动、额外回合等插队行动。
    ActionTopState action_top;

    // 全队共享资源，例如战技点。
    ResourcesState resources;

    // 被插队行动暂停的普通行动角色 id。空字符串表示没有被暂停的角色。
    std::string suspended_normal_actor_id = "";

    // 上一次技能/行动结算结果。空 optional 表示当前没有结算结果。
    std::optional<SkillResult> last_result;

    // 当前 active actor 载荷。空指针表示当前没有 active actor。
    std::unique_ptr<Actor> active_actor;

    GameState() : GameState(0, "", 0) {}

    GameState(
        int tick,
        std::string phase,
        int phase_remaining_ticks,
        int turn = 0,
        std::string current_actor_id = "",
        std::optional<CurrentActionState> current_action = std::nullopt,
        std::string message = "",
        std::string error = "",
        double error_time = 0.0,
        std::vector<std::string> log = {},
        ActionQueueState action_queue = {},
        ActionTopState action_top = {},
        ResourcesState resources = {},
        std::string suspended_normal_actor_id = "",
        std::optional<SkillResult> last_result = std::nullopt,
        std::unique_ptr<Actor> active_actor = nullptr
    )
        : tick(tick),
          phase(std::move(phase)),
          phase_remaining_ticks(phase_remaining_ticks),
          turn(turn),
          current_actor_id(std::move(current_actor_id)),
          current_action(std::move(current_action)),
          message(std::move(message)),
          error(std::move(error)),
          error_time(error_time),
          log(std::move(log)),
          action_queue(std::move(action_queue)),
          action_top(std::move(action_top)),
          resources(std::move(resources)),
          suspended_normal_actor_id(std::move(suspended_normal_actor_id)),
          last_result(std::move(last_result)),
          active_actor(std::move(active_actor)) {}

    // 值语义：复制时深拷贝队列与 active actor。
    GameState(const GameState& other)
        : tick(other.tick),
          phase(other.phase),
          phase_remaining_ticks(other.phase_remaining_ticks),
          turn(other.turn),
          current_actor_id(other.current_actor_id),
          current_action(other.current_action),
          message(other.message),
          error(other.error),
          error_time(other.error_time),
          log(other.log),
          action_queue(other.action_queue),
          action_top(other.action_top),
          resources(other.resources),
          suspended_normal_actor_id(other.suspended_normal_actor_id),
          last_result(other.last_result),
          active_actor(other.active_actor ? other.active_actor->clone() : nullptr) {}

    GameState& operator=(const GameState& other) {
        if (this != &other) {
            tick = other.tick;
            phase = other.phase;
            phase_remaining_ticks = other.phase_remaining_ticks;
            turn = other.turn;
            current_actor_id = other.current_actor_id;
            current_action = other.current_action;
            message = other.message;
            error = other.error;
            error_time = other.error_time;
            log = other.log;
            action_queue = other.action_queue;
            action_top = other.action_top;
            resources = other.resources;
            suspended_normal_actor_id = other.suspended_normal_actor_id;
            last_result = other.last_result;
            active_actor = other.active_actor ? other.active_actor->clone() : nullptr;
        }
        return *this;
    }

    GameState(GameState&&) = default;
    GameState& operator=(GameState&&) = default;
};

}  // namespace srs
