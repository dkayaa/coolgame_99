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
}
