#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "BodyTwo.h"
#include "VectorTwo.h"
#include <limits>

namespace PEngine
{
    class Collisions
    {
    public:
        static bool intersectBodies(BodyTwo *b1, BodyTwo *b2, VectorTwo *n, double *mag);
        static bool intersectCircles(BodyTwo *c1, BodyTwo *c2, VectorTwo *n, double *mag);
        static bool intersectRect(BodyTwo *r1, BodyTwo *r2, VectorTwo *n, double *mag);
        static bool intersectCircleRect(BodyTwo *r, BodyTwo *c, VectorTwo *n, double *mag);
        static bool intersectPointRect(BodyTwo *p, BodyTwo *r, VectorTwo *n, double *mag);

    private:
        static void projectVertices(VectorTwo *v, int n, VectorTwo axis, double *min, double *max);
        static void projectCircle(BodyTwo *c, VectorTwo axis, double *min, double *max);
        static VectorTwo getClosestPointRect(BodyTwo *c, BodyTwo *r);
    };
}

#endif