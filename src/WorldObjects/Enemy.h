#ifndef ENEMY_H
#define ENEMY_H
#include "GameEntity.h"
namespace PEngine
{
    class VectorTwo;
    class BodyTwo;
}

namespace WorldObjects
{
    class Enemy : public GameEntity
    {
    private:
        PEngine::BodyTwo *player_ = nullptr;                     // Will have to change this to a players array.
        PEngine::VectorTwo s_vector_ = PEngine::VectorTwo(0, 0); // Sight vector, points from the enemy to the player.
        double s_radius_ = 80.0;                                 // Sight Radius, player spotted if its within this radius
    public:
        Enemy() = delete;
        Enemy(PEngine::VectorTwo position);
        Enemy(PEngine::VectorTwo position, double radius);
        Enemy(PEngine::VectorTwo position, double radius, PEngine::BodyTwo *player);

        void SetPlayer(PEngine::BodyTwo *player);
        void ComputeSVector();
        bool HasLOS();
        // virtual void Step(float dt) override;
    };
}

#endif