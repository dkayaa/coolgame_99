#include "GameEntity.h"
#include "../PEngine/VectorTwo.h"
#include "../PEngine/BodyTwo.h"
#include "../classes.h"

namespace WorldObjects
{
    GameEntity::GameEntity(PEngine::VectorTwo position) : PEngine::BodyTwo(position, PEngine::VectorTwo(0, 0), 0.0, 0.0, 0.0, 0.0, 0.0, PEngine::ShapeType::POINT, true, false)
    {
        compute_vertices_function_ = ObjectVertexComputers::ComputePointVertices;
        class_type_ = PEngine::ClassType::GAMEENTITY;
        id_ = next_id_++;
    }

    GameEntity::GameEntity(PEngine::VectorTwo position, PEngine::VectorTwo velocity, double mass, double rotation, double radius, double width, double length, PEngine::ShapeType type, bool is_static, bool is_solid) : PEngine::BodyTwo(position, velocity, mass, rotation, radius, width, length, type, is_static, is_solid)
    {
        compute_vertices_function_ = ObjectVertexComputers::ComputePointVertices;
        class_type_ = PEngine::ClassType::GAMEENTITY;
        id_ = next_id_++;
    }

    void GameEntity::AddFixedNeighbour(GameEntity *n)
    {
        if (fixed_neighbours_index_ >= max_fixed_neighbours_)
        {
            return;
        }

        if (fixed_neighbours_ == nullptr)
        {
            fixed_neighbours_ = (GameEntity **)malloc(sizeof(GameEntity *) * max_fixed_neighbours_);
            fixed_neighbours_index_ = 0;
        }

        fixed_neighbours_[fixed_neighbours_index_] = n;
        fixed_neighbours_index_++;
        return;
    }
    void GameEntity::AddVariableNeighbour(GameEntity *n)
    {
        if (variable_neighbours_index_ >= max_variable_neighbours_)
        {
            return;
        }

        if (variable_neighbours_ == nullptr)
        {
            variable_neighbours_ = (GameEntity **)malloc(sizeof(GameEntity *) * max_variable_neighbours_);
            variable_neighbours_index_ = 0;
        }

        variable_neighbours_[variable_neighbours_index_] = n;
        variable_neighbours_index_++;
        return;
    }
    int GameEntity::GetNumFixedNeighbours()
    {
        return fixed_neighbours_index_;
    }
    int GameEntity::GetNumVariableNeighbours()
    {
        return variable_neighbours_index_;
    }

    void GameEntity::ClearVariableNeighbours()
    {
        variable_neighbours_index_ = 0;
    }

    GameEntity *GameEntity::GetFixedNeighbourAtIndex(int i)
    {
        if (i >= fixed_neighbours_index_)
        {
            return nullptr;
        }
        return fixed_neighbours_[i];
    }
    GameEntity *GameEntity::GetVariableNeighbourAtIndex(int i)
    {
        if (i >= variable_neighbours_index_)
        {
            return nullptr;
        }
        return variable_neighbours_[i];
    }
    bool GameEntity::operator==(const GameEntity &other) const
    {
        return (*this).id_ == other.id_;
    }

    void GameEntity::Reset(void)
    {
        (*this).ClearVariableNeighbours();
        (*this).setV(PEngine::VectorTwo(0, 0));
    }

    int GameEntity::GetID(void)
    {
        return id_;
    }
}
