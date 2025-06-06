#include "Goal.h"
#include "../classes.h"
#include "../PEngine/VectorTwo.h"
#include "../PEngine/BodyTwo.h"
#include "GameEntity.h"

namespace WorldObjects
{
    Goal::Goal(PEngine::VectorTwo position) : GameEntity(position, PEngine::VectorTwo(0, 0), 0.0, 0.0, 0.0, 1.0, 1.0, PEngine::ShapeType::RECT, true, false)
    {
        compute_vertices_function_ = ObjectVertexComputers::ComputeRectVertices;
        class_type_ = PEngine::ClassType::GOAL;
        fill_colour_ = PEngine::ShapeColour::BLUE;
    }

    Goal::Goal(PEngine::VectorTwo position, double length) : GameEntity(position, PEngine::VectorTwo(0, 0), 0.0, 0.0, 0.0, length, length, PEngine::ShapeType::RECT, true, false)
    {
        compute_vertices_function_ = ObjectVertexComputers::ComputeRectVertices;
        class_type_ = PEngine::ClassType::GOAL;
        fill_colour_ = PEngine::ShapeColour::BLUE;
    }
}
