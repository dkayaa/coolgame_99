#include "OGTile.h"
#include "../classes.h"
#include "../PEngine/VectorTwo.h"
#include "../PEngine/BodyTwo.h"
#include "GameEntity.h"

namespace WorldObjects
{
    OGTile::OGTile(PEngine::VectorTwo position) : GameEntity(position, PEngine::VectorTwo(0, 0), 0.0, 0.0, 0.0, 1.0, 1.0, PEngine::ShapeType::RECT, true, true)
    {
        compute_vertices_function_ = ObjectVertexComputers::ComputeRectVertices;
        class_type_ = PEngine::ClassType::OGTILE;
    }

    OGTile::OGTile(PEngine::VectorTwo position, double length) : GameEntity(position, PEngine::VectorTwo(0, 0), 0.0, 0.0, 0.0, length, length, PEngine::ShapeType::RECT, true, true)
    {
        compute_vertices_function_ = ObjectVertexComputers::ComputeRectVertices;
        class_type_ = PEngine::ClassType::OGTILE;
    }
}
