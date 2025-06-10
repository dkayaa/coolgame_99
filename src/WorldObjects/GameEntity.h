#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "../PEngine/BodyTwo.h"
#include <atomic>
#include <SDL3_image/SDL_image.h>
#include "string"

namespace PEngine
{
    class VectorTwo;
}

namespace WorldObjects
{
    enum OccupancyState
    {
        NONE,
        ENEMY,
        PLAYER,
        BOTH
    };

    class GameEntity : public PEngine::BodyTwo
    {
    private:
        static inline std::atomic<int> next_id_ = 0;
        int id_;

        GameEntity **fixed_neighbours_ = nullptr;
        int max_fixed_neighbours_ = 8;
        int fixed_neighbours_index_ = 0;

        GameEntity **variable_neighbours_ = nullptr;
        int max_variable_neighbours_ = 99;
        int variable_neighbours_index_ = 0;

        bool print_texture_ = false;
        SDL_Texture **textures_ = nullptr;

    public:
        GameEntity() = delete;
        GameEntity(PEngine::VectorTwo position);
        GameEntity(PEngine::VectorTwo position, PEngine::VectorTwo velocity, double mass, double rotation, double radius, double width, double length, PEngine::ShapeType type, bool is_static, bool is_solid);

        void AddFixedNeighbour(GameEntity *n);
        void AddVariableNeighbour(GameEntity *n);
        int GetNumFixedNeighbours();
        int GetNumVariableNeighbours();
        void ClearVariableNeighbours();
        GameEntity *GetFixedNeighbourAtIndex(int i);
        GameEntity *GetVariableNeighbourAtIndex(int i);

        void Reset(void);
        int GetID(void);
        bool operator==(const GameEntity &other) const;
    };
}
#endif
