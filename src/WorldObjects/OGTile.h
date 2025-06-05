#ifndef WALL_H
#define WALL_H
#include "GameEntity.h"

namespace PEngine
{
    class VectorTwo;
}

namespace WorldObjects
{
    class OGTile : public GameEntity
    {
    private:
    public:
        OGTile() = delete;
        OGTile(PEngine::VectorTwo position);
        OGTile(PEngine::VectorTwo position, double length);
    };
}
#endif