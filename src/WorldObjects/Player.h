#ifndef PLAYER_H
#define PLAYER_H
#include "GameEntity.h"

namespace PEngine
{
    class VectorTwo;
}

namespace WorldObjects
{
    class Player : public GameEntity
    {
    private:
    public:
        Player() = delete;
        Player(PEngine::VectorTwo position);
        Player(PEngine::VectorTwo position, double radius);
    };
}

#endif