#ifndef FLOOR_H
#define FLOOR_H

#include "../PEngine/BodyTwo.h"
#include "../PEngine/VectorTwo.h"
#include "GameEntity.h"

namespace WorldObjects
{
    class Floor : public GameEntity
    {
    private:
    public:
        Floor() = delete;
        Floor(PEngine::VectorTwo position);
    };
}
#endif