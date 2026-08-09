#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace srs
{

struct Actor
{
public:
    uint64_t id;

protected:
    Actor(uint64_t id = 0): id(id){};
};

struct Character : Actor
{
public:
    double speed = 0.0;
};

struct Enemy : Actor
{
public:
    double speed = 0.0;
};

}
