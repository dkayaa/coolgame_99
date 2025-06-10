#ifndef HELPERS_H
#define HELPERS_H

#include <cstdlib>
#include <time.h>
#include <iostream>
#include "PEngine/BodyTwo.h"

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