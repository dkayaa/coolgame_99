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
        Floor **neighbours_ = nullptr;
        // int n_neighbours_ = 0;
        int max_neighbours_ = 9;
        int neighbours_index_ = -1;

    public:
        Floor() = delete;
        Floor(PEngine::VectorTwo position);
        void AddNeighbour(Floor *neighbour);
        int GetNumNeighbours();
        Floor *GetNeighbourAtIndex(int i);
    };
}
#endif