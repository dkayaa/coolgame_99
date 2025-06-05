#include "Collisions.h"
#include <limits>

using namespace PEngine;

bool Collisions::intersectBodies(BodyTwo *b1, BodyTwo *b2, VectorTwo *n, double *mag)
{
    if (!b1->isSolid() || !b2->isSolid())
    {
        return false;
    }

    if ((b1->getType() == ShapeType::CIRCLE) && (b2->getType() == ShapeType::CIRCLE))
        return intersectCircles(b1, b2, n, mag);

    if ((b1->getType() == ShapeType::RECT) && (b2->getType() == ShapeType::RECT))
        return intersectRect(b1, b2, n, mag);

    if ((b1->getType() == ShapeType::RECT) && (b2->getType() == ShapeType::CIRCLE))
        return intersectCircleRect(b1, b2, n, mag);

    if ((b1->getType() == ShapeType::CIRCLE) && (b2->getType() == ShapeType::RECT))
        return intersectCircleRect(b2, b1, n, mag);

    return false;
}
bool Collisions::intersectCircles(BodyTwo *c1, BodyTwo *c2, VectorTwo *n, double *mag)
{

    if (VectorTwo::Distance(c1->getPos(), c2->getPos()) >= (c1->getRadius() + c2->getRadius()))
    {
        return false;
    }

    (*mag) = (c1->getRadius() + c2->getRadius()) - VectorTwo::Distance(c1->getPos(), c2->getPos());
    (*n) = VectorTwo::Normalise(c2->getPos() - c1->getPos());
    return true;
}

bool Collisions::intersectRect(BodyTwo *r1, BodyTwo *r2, VectorTwo *n, double *mag)
{
    VectorTwo *v1 = r1->getCachedVerts();
    VectorTwo *v2 = r2->getCachedVerts();
    int num1 = r1->getNVert();
    int num2 = r2->getNVert();

    *mag = std::numeric_limits<double>::max();

    for (int i = 0; i < num1; i++)
    {
        VectorTwo a = v1[i];
        VectorTwo b = v1[(i + 1) % num1];

        VectorTwo e = b - a;
        VectorTwo axis = VectorTwo(-e.getY(), e.getX());

        axis = VectorTwo::Normalise(axis);

        double min1, min2;
        double max1, max2;
        projectVertices(v1, num1, axis, &min1, &max1);
        projectVertices(v2, num2, axis, &min2, &max2);

        if (min1 >= max2 || min2 >= max1)
        {
            return false;
        }

        if (max2 - min1 < *mag)
        {
            *mag = max2 - min1;
            *n = axis;
        }
        if (max1 - min2 < *mag)
        {
            *mag = max1 - min2;
            *n = axis;
        }
    }

    for (int i = 0; i < num2; i++)
    {
        VectorTwo a = v2[i];
        VectorTwo b = v2[(i + 1) % num2];

        VectorTwo e = b - a;
        VectorTwo axis = VectorTwo(-e.getY(), e.getX());

        axis = VectorTwo::Normalise(axis);

        double min1, min2;
        double max1, max2;
        projectVertices(v1, num2, axis, &min1, &max1);
        projectVertices(v2, num2, axis, &min2, &max2);

        if (min1 >= max2 || min2 >= max1)
        {
            return false;
        }

        if (max2 - min1 < *mag)
        {
            *mag = max2 - min1;
            *n = axis;
        }
        if (max1 - min2 < *mag)
        {
            *mag = max1 - min2;
            *n = axis;
        }
    }

    VectorTwo nd = r2->getPos() - r1->getPos();
    if (VectorTwo::Dot(nd, (*n)) < 0)
    {
        (*n) = -(*n);
    }

    //*mag /= VectorTwo::Length(*n);
    //*n = VectorTwo::Normalise(*n);
    return true;
}

bool Collisions::intersectCircleRect(BodyTwo *r, BodyTwo *c, VectorTwo *n, double *mag)
{

    VectorTwo *v = r->getCachedVerts();
    int num = r->getNVert();

    *mag = std::numeric_limits<double>::max();

    VectorTwo axis = VectorTwo(0, 0);

    for (int i = 0; i < num; i++)
    {
        VectorTwo a = v[i];
        VectorTwo b = v[(i + 1) % num];

        VectorTwo e = b - a;
        axis = VectorTwo(e.getY(), -e.getX());

        axis = VectorTwo::Normalise(axis);

        double min1, min2;
        double max1, max2;
        projectVertices(v, num, axis, &min1, &max1);
        projectCircle(c, axis, &min2, &max2);

        if (min1 >= max2 || min2 >= max1)
        {
            return false;
        }

        if (max2 - min1 < *mag)
        {
            *mag = max2 - min1;
            *n = axis;
        }
        if (max1 - min2 < *mag)
        {
            *mag = max1 - min2;
            *n = axis;
        }
    }
    VectorTwo a = c->getPos();
    VectorTwo b = getClosestPointRect(c, r);

    // VectorTwo e = b - a;
    axis = b - a;

    axis = VectorTwo::Normalise(axis);

    double min1, min2;
    double max1, max2;
    projectVertices(v, num, axis, &min1, &max1);
    projectCircle(c, axis, &min2, &max2);

    if (min1 >= max2 || min2 >= max1)
    {
        return false;
    }

    if (max2 - min1 < *mag)
    {
        *mag = max2 - min1;
        *n = axis;
    }
    if (max1 - min2 < *mag)
    {
        *mag = max1 - min2;
        *n = axis;
    }

    VectorTwo nd = r->getPos() - c->getPos();
    if (VectorTwo::Dot(nd, (*n)) < 0)
    {
        (*n) = -(*n);
    }

    //*mag /= VectorTwo::Length(*n);
    //*n = VectorTwo::Normalise(*n);
    return true;
}

bool Collisions::intersectPointRect(BodyTwo *p, BodyTwo *r, VectorTwo *n, double *mag)
{

    VectorTwo *v = r->getCachedVerts();
    int num = r->getNVert();

    *mag = 0;
    *n = VectorTwo(0, 0);

    VectorTwo axis = VectorTwo(0, 0);

    for (int i = 0; i < num; i++)
    {
        VectorTwo a = v[i];
        VectorTwo b = v[(i + 1) % num];

        VectorTwo e = b - a;
        axis = VectorTwo(e.getY(), -e.getX());

        axis = VectorTwo::Normalise(axis);

        double min1;
        double max1;
        projectVertices(v, num, axis, &min1, &max1);
        // projectCircle(c, axis, &min2, &max2);

        auto pp = VectorTwo::Dot(p->getPos(), axis);

        if (pp > max1 || pp < min1)
        {
            return false;
        }
    }
    VectorTwo a = p->getPos();
    VectorTwo b = getClosestPointRect(p, r);

    // VectorTwo e = b - a;
    axis = b - a;

    axis = VectorTwo::Normalise(axis);

    double min1;
    double max1;
    projectVertices(v, num, axis, &min1, &max1);
    // projectCircle(c, axis, &min2, &max2);
    auto pp = VectorTwo::Dot(p->getPos(), axis);

    if (pp > max1 || pp < min1)
    {
        return false;
    }

    return true;
}

void Collisions::projectVertices(VectorTwo *vs, int n, VectorTwo axis, double *min, double *max)
{
    *min = std::numeric_limits<double>::max();
    *max = std::numeric_limits<double>::min();

    for (int i = 0; i < n; i++)
    {
        VectorTwo v = vs[i];
        double proj = VectorTwo::Dot(v, axis);
        if (proj < *min)
        {
            *min = proj;
        }
        if (proj > *max)
        {
            *max = proj;
        }
    }
    return;
}

void Collisions::projectCircle(BodyTwo *c, VectorTwo axis, double *min, double *max)
{
    VectorTwo dir = VectorTwo::Normalise(axis);
    VectorTwo p1 = c->getPos() + (dir * (c->getRadius()));
    VectorTwo p2 = c->getPos() - (dir * (c->getRadius()));

    *max = VectorTwo::Dot(p1, axis);
    *min = VectorTwo::Dot(p2, axis);

    if (*max < *min)
    {
        double t = *min;
        *min = *max;
        *max = t;
    }

    return;
}

VectorTwo Collisions::getClosestPointRect(BodyTwo *c, BodyTwo *r)
{
    double min = std::numeric_limits<double>::max();
    int n = r->getNVert();
    VectorTwo mv = VectorTwo(0, 0);
    VectorTwo *v = r->getCachedVerts();
    for (int i = 0; i < n; i++)
    {
        double dist = VectorTwo::Distance(c->getPos(), v[i]);
        if (dist < min)
        {
            mv = v[i];
            min = dist;
        }
    }

    return mv;
}
