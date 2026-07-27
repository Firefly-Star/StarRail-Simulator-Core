#pragma once

#include <string>
#include <vector>

namespace srs {

struct InputEvent {
    char key;
    double timestamp;

    InputEvent() : key(0), timestamp(0.0) {}
    InputEvent(char key, double timestamp = 0.0) : key(key), timestamp(timestamp) {}
};

struct BattleConfig {
    struct Character {
        std::string id;
        std::string name;
        int speed;
        int max_energy;
        bool is_enemy;
        int position;

        Character() : speed(0), max_energy(0), is_enemy(false), position(0) {}
        Character(std::string id, std::string name, int speed, int max_energy, bool is_enemy, int position)
            : id(std::move(id)), name(std::move(name)), speed(speed), max_energy(max_energy),
              is_enemy(is_enemy), position(position) {}
    };
    std::vector<Character> characters;
};

struct TickSnapshot {
    struct QueueItem {
        double current_av;
        std::string char_id;
        std::string name;
        int speed;
        bool is_enemy;
        int energy;
        int max_energy;
        int position;

        QueueItem() : current_av(0.0), speed(0), is_enemy(false), energy(0), max_energy(0), position(0) {}
    };

    int tick = 0;
    int turn = 0;
    std::string phase;
    int phase_remaining_ticks = 0;
    std::string message;
    std::string error;
    std::vector<std::string> log;
    std::vector<QueueItem> action_queue;
    std::vector<std::string> top_queue;
    int skill_points = 3;
    int max_skill_points = 5;

    std::string current_actor_id;
    std::string current_actor_name;
    int current_actor_speed = 0;
    int current_actor_energy = 0;
    int current_actor_max_energy = 0;
    int current_actor_position = 0;
    bool is_enemy_turn = false;
};

class BattleEngine {
public:
    void init(const BattleConfig& config);

    TickSnapshot tick(const std::vector<InputEvent>& inputs);

    bool is_over() const;

private:
    int tick_count_ = 0;
    BattleConfig config_;
    bool over_ = false;
};

}  // namespace srs
