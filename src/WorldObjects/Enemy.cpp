#include "Enemy.h"
#include "../PEngine/VectorTwo.h"
#include "../PEngine/BodyTwo.h"
#include "GameEntity.h"
namespace WorldObjects
{
    Enemy::Enemy(PEngine::VectorTwo position) : GameEntity(position, PEngine::VectorTwo(0, 0), 0.0, 0.0, 1.0, 0.0, 0.0, PEngine::ShapeType::CIRCLE, false, true)
    {
        compute_vertices_function_ = ObjectVertexComputers::ComputeCircleVertices;
        class_type_ = PEngine::ClassType::ENEMY;
    }

    Enemy::Enemy(PEngine::VectorTwo position, double radius) : GameEntity(position, PEngine::VectorTwo(0, 0), 0.0, 0.0, radius, 0.0, 0.0, PEngine::ShapeType::CIRCLE, false, true)
    {
        compute_vertices_function_ = ObjectVertexComputers::ComputeCircleVertices;
        class_type_ = PEngine::ClassType::ENEMY;
    }

    Enemy::Enemy(PEngine::VectorTwo position, double radius, PEngine::BodyTwo *player) : GameEntity(position, PEngine::VectorTwo(0, 0), 0.0, 0.0, radius, 0.0, 0.0, PEngine::ShapeType::CIRCLE, false, true)
    {
        compute_vertices_function_ = ObjectVertexComputers::ComputeCircleVertices;
        class_type_ = PEngine::ClassType::ENEMY;
        player_ = player;
    }

    void Enemy::SetPlayer(PEngine::BodyTwo *player)
    {
        player_ = player;
    }

    void Enemy::ComputeSVector()
    {
        s_vector_ = (*player_).getPos() - (*this).getPos();
    }

    bool Enemy::HasLOS()
    {
        (*this).ComputeSVector();
        if (PEngine::VectorTwo::Length(s_vector_) <= s_radius_)
        {
            return true;
        }
        return false;
    }

    // void Enemy::Step(float dt)
    //{
    //     if ((*this).HasLOS())
    //     {
    //         (*this).setV(PEngine::VectorTwo::Normalise(s_vector_) * 200.0);
    //         (*this).Move((*this).getV() * dt);
    //     }
    // }
}
