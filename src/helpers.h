#ifndef HELPERS_H
#define HELPERS_H

#include <cstdlib>
#include <time.h>
#include <iostream>
#include "PEngine/BodyTwo.h"

// bool overlaps(Hitbox a, Hitbox b);
// bool overlaps(double x1, double x2, int w1, int w2);
// bool overlaps(Hitbox a, Hitbox b);
// bool overlaps(double x1, double x2, int w1, int w2);
// PhysicsVector getNextPos(PhysicsVector &p, PhysicsVector &v, PhysicsVector &a, double dt);

namespace Helpers
{
    class RandomHelper
    {
    private:
        unsigned int seed_;

    public:
        RandomHelper()
        {
            seed_ = time(NULL);
        };
        RandomHelper(unsigned int seed)
        {
            seed_ = seed;
            srand(seed_);
        }
        ~RandomHelper() {};
        int randInRange(int min, int max)
        {
            int range = max - min;
            return (rand() % range + min);
        }
    };
}

#endif