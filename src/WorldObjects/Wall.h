#ifndef WALL_H
#define WALL_H
#include "GameEntity.h"

namespace PEngine
{
    class VectorTwo;
}

namespace WorldObjects
{
    class Wall : public GameEntity
    {
    private:
    public:
        Wall() = delete;
        Wall(PEngine::VectorTwo position);
        Wall(PEngine::VectorTwo position, double length);
    };
}
#endif