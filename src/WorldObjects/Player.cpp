#include "Player.h"
#include "../PEngine/VectorTwo.h"
#include "../PEngine/BodyTwo.h"
#include "GameEntity.h"
namespace WorldObjects
{
    Player::Player(PEngine::VectorTwo position) : GameEntity(position, PEngine::VectorTwo(0, 0), 0.0, 0.0, 1.0, 0.0, 0.0, PEngine::ShapeType::CIRCLE, false, true)
    {
        compute_vertices_function_ = ObjectVertexComputers::ComputeCircleVertices;
        class_type_ = PEngine::ClassType::PLAYER;
    }

    Player::Player(PEngine::VectorTwo position, double radius) : GameEntity(position, PEngine::VectorTwo(0, 0), 0.0, 0.0, radius, 0.0, 0.0, PEngine::ShapeType::CIRCLE, false, true)
    {
        compute_vertices_function_ = ObjectVertexComputers::ComputeCircleVertices;
        class_type_ = PEngine::ClassType::PLAYER;
    }
}
