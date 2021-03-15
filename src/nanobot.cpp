#include "nanobot.h"

Nanobot::Nanobot()
{
    _type = EntityType::kNanobot;
    _mode = BotMode::kNesting;
    _range = 100.0;
}

void Nanobot::simulate()
{
    // launch drive function in a thread
    threads.emplace_back(std::thread(&Nanobot::move, this));
}

void Nanobot::move()
{
    return;
}