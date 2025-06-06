#ifndef GOAL_H
#define GOAL_H
#include "GameEntity.h"

namespace PEngine
{
    class VectorTwo;
}

namespace WorldObjects
{
    class Goal : public GameEntity
    {
    private:
    public:
        Goal() = delete;
        Goal(PEngine::VectorTwo position);
        Goal(PEngine::VectorTwo position, double length);
    };
}
#endif