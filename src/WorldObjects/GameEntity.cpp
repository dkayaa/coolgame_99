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
    void GameEntity::AddNeighbour(GameEntity *neighbour)
    {
        if (neighbours_index_ >= max_neighbours_)
        {
            return;
        }

        if (neighbours_ == nullptr)
        {
            neighbours_ = (GameEntity **)malloc(sizeof(GameEntity *) * max_neighbours_);
            neighbours_index_ = 0;
        }

        neighbours_[neighbours_index_] = neighbour;
        neighbours_index_++;
        return;
    }

    int GameEntity::GetNumNeighbours()
    {
        return neighbours_index_;
    }

    void GameEntity::SetRequiresNeighboursComp(bool val)
    {
        requires_neighbours_computation_ = val;
    }

    GameEntity *GameEntity::GetNeighbourAtIndex(int i)
    {
        if (i >= neighbours_index_)
        {
            return nullptr;
        }
        return neighbours_[i];
    }

    void GameEntity::ClearNeighbours()
    {
        for (int i = 0; i < neighbours_index_; i++)
        {
            neighbours_[i]->SetRequiresNeighboursComp(true);
        }
        this->SetRequiresNeighboursComp(true);
        // free(neighbours_);
        neighbours_index_ = 0;
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
        (*this).SetState(WorldObjects::OccupancyState::NONE);
        (*this).ClearVariableNeighbours();
    }

    int GameEntity::GetID(void)
    {
        return id_;
    }

    OccupancyState &GameEntity::GetState(void)
    {
        return occ_state_;
    }
    void GameEntity::SetState(OccupancyState state)
    {
        occ_state_ = state;
    }
}
