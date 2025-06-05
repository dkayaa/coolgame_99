#include "Floor.h"
#include "../PEngine/VectorTwo.h"
#include "../PEngine/BodyTwo.h"
#include "../classes.h"
#include "GameEntity.h"

namespace WorldObjects
{
    Floor::Floor(PEngine::VectorTwo position) : GameEntity(position, PEngine::VectorTwo(0, 0), 0.0, 0.0, 0.0, 0.0, 0.0, PEngine::ShapeType::POINT, true, false)
    {
        compute_vertices_function_ = ObjectVertexComputers::ComputePointVertices;
        class_type_ = PEngine::ClassType::FLOOR;
    }

    // void Floor::AddNeighbour(Floor *neighbour)
    //{
    //     if (neighbours_index_ >= max_neighbours_)
    //     {
    //         return;
    //     }

    //    if (neighbours_ == nullptr)
    //    {
    //        neighbours_ = (Floor **)malloc(sizeof(Floor *) * max_neighbours_);
    //        neighbours_index_ = 0;
    //    }

    //    neighbours_[neighbours_index_] = neighbour;
    //    neighbours_index_++;
    //    return;
    //}

    // int Floor::GetNumNeighbours()
    //{
    //     return neighbours_index_;
    // }

    // Floor *Floor::GetNeighbourAtIndex(int i)
    //{
    //     if (i >= neighbours_index_)
    //     {
    //         return nullptr;
    //     }
    //     return neighbours_[i];
    // }

}
