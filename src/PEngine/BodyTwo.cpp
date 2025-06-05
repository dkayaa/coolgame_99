#include "VectorTwo.h"
#include "BodyTwo.h"
#include <iostream>
#include <assert.h>
namespace PEngine
{
    void BodyTwo::DoComputeVerts(void)
    {
        compute_vertices_function_(&vertices_, this, &n_vert_);
    }

    void BodyTwo::Move(VectorTwo v)
    {
        (*this).position_ += v;
        for (int i = 0; i < n_vert_; i++)
        {
            vertices_[i] += v;
        }
    }

    void BodyTwo::MoveTo(VectorTwo p)
    {
        (*this).position_ = p;
        // computeVerts();
    }

    bool BodyTwo::canMove(void)
    {
        return !(*this).is_static_;
    }

    bool BodyTwo::isSolid(void)
    {
        return (*this).is_solid_;
    }

    VectorTwo &BodyTwo::getPos(void)
    {
        return position_;
    }
    VectorTwo &BodyTwo::getV(void)
    {
        return velocity_;
    }
    double BodyTwo::getM(void)
    {
        return mass_;
    }
    double BodyTwo::getRot(void)
    {
        return rotation_;
    }
    double BodyTwo::getRadius(void)
    {
        return radius_;
    }
    double BodyTwo::getW(void)
    {
        return width_;
    }
    double BodyTwo::getL(void)
    {
        return length_;
    }
    ShapeType &BodyTwo::getType(void)
    {
        return type_;
    }

    ClassType &BodyTwo::getClassType(void)
    {
        return class_type_;
    }

    void BodyTwo::setV(VectorTwo v)
    {
        velocity_ = v;
    }

    void BodyTwo::setColour(ShapeColour colour)
    {
        colour_ = colour;
    }

    void BodyTwo::setFillColour(ShapeColour colour)
    {
        fill_colour_ = colour;
    }

    ShapeColour BodyTwo::getColour()
    {
        return (*this).colour_;
    }

    ShapeColour BodyTwo::getFillColour()
    {
        return (*this).fill_colour_;
    }

    int BodyTwo::getNVert(void)
    {
        return n_vert_;
    }
    VectorTwo *BodyTwo::getCachedVerts(void)
    {
        return vertices_;
    }

    void BodyTwo::Step(float dt)
    {
        (*this).Move(((*this)).getV() * dt);
    }

    void BodyTwo::computeVerts(void)
    {
        return;
    }
}