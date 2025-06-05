#include "helpers.h"
#include "defines.h"
#include "classes.h"
#include "peripherals.h"
#include "app.h"
#include <cmath>
#include <SDL3/SDL.h>

// bool overlaps(Hitbox a, Hitbox b)
//{
//     return overlaps(a.position.x, b.position.x, a.w, b.w) &&
//            overlaps(a.position.y, b.position.y, a.d, b.d) &&
//            overlaps(a.position.z, b.position.z, a.h, b.h);
// }

// bool overlaps(double x1, double x2, int w1, int w2)
//{
//     double m1 = (x1 + w1) * 0.5;
//     double m2 = (x2 + w2) * 0.5;

//    double dist = abs(m1 - m2);
//    double threshold = w1 * 0.5 + w2 * 0.5;

//    if (dist < threshold)
//    {
//        return true;
//    }

//    return false;
//}

// PhysicsVector getNextPos(PhysicsVector &p, PhysicsVector &v, PhysicsVector &a, double dt)
//{
//     PhysicsVector newp;
//     newp.x = p.x + v.x * dt + (0.5) * a.x * pow(dt, 2.0);
//     newp.y = p.y + v.y * dt + (0.5) * a.y * pow(dt, 2.0);
//     newp.z = p.z + v.z * dt + (0.5) * a.z * pow(dt, 2.0);
//     return newp;
// }