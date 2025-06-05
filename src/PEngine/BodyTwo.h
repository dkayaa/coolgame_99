#ifndef BODYTWO_H
#define BODYTWO_H

#include "VectorTwo.h"
#include "../classes.h"
namespace PEngine
{
    typedef void (*ComputeVerticesFunction)(PEngine::VectorTwo **, PEngine::BodyTwo *, int *);

    enum ShapeType
    {
        CIRCLE,
        RECT,
        POINT,
        OTHER
    };

    enum ClassType
    {
        GAMEENTITY,
        CIRC,
        REC,
        BODY,
        FLOOR,
        PLAYER,
        WALL,
        ENEMY,
        OGTILE,
        MISC
    };

    enum ShapeColour
    {
        BLACK,
        WHITE,
        RED,
        BLUE,
        GREEN
    };

    // Rigid Body class for 2d Objects
    class BodyTwo
    {

    protected:
        VectorTwo position_ = VectorTwo(0, 0);
        VectorTwo velocity_ = VectorTwo(0, 0);
        VectorTwo *vertices_ = nullptr;
        int n_vert_ = 0;
        double mass_ = 0.0;
        double inv_mass_ = 0.0;
        double restitution = 0.0;
        double rotation_ = 0.0;
        double radius_ = 0.0;
        double width_ = 0.0;
        double length_ = 0.0;
        bool is_static_ = false;
        bool is_solid_ = true;
        ShapeType type_ = ShapeType::OTHER;
        ShapeColour colour_ = ShapeColour::WHITE;
        ShapeColour fill_colour_ = ShapeColour::BLACK;
        ClassType class_type_ = ClassType::BODY;
        ComputeVerticesFunction compute_vertices_function_ = ObjectVertexComputers::ComputePointVertices;

    public:
        BodyTwo() {};
        BodyTwo(VectorTwo position, VectorTwo velocity, double mass, double rotation, double radius, double width, double length, ShapeType type) : position_{position}, velocity_{velocity}, mass_{mass}, rotation_{rotation}, radius_{radius}, width_{width}, length_{length}, type_{type} {};
        BodyTwo(VectorTwo position, VectorTwo velocity, double mass, double rotation, double radius, double width, double length, ShapeType type, bool is_static) : position_{position}, velocity_{velocity}, mass_{mass}, rotation_{rotation}, radius_{radius}, width_{width}, length_{length}, type_{type}, is_static_{is_static} {};
        BodyTwo(VectorTwo position, VectorTwo velocity, double mass, double rotation, double radius, double width, double length, ShapeType type, bool is_static, bool is_solid) : position_{position}, velocity_{velocity}, mass_{mass}, rotation_{rotation}, radius_{radius}, width_{width}, length_{length}, type_{type}, is_static_{is_static}, is_solid_{is_solid} {};

        BodyTwo &operator*(BodyTwo &other) = delete;
        BodyTwo &operator/(BodyTwo &other) = delete;
        BodyTwo &operator+(BodyTwo &other) = delete;
        BodyTwo &operator-(BodyTwo &other) = delete;

        void Move(VectorTwo v);
        void MoveTo(VectorTwo p);
        bool canMove(void);
        bool isSolid(void);

        VectorTwo &getPos(void);
        VectorTwo &getV(void);
        double getM(void);
        double getRot(void);
        double getRadius(void);
        double getW(void);
        double getL(void);
        ShapeType &getType(void);
        ClassType &getClassType(void);

        int getNVert(void);
        VectorTwo *getCachedVerts(void);
        virtual void Step(float dt);
        virtual void computeVerts(void);
        void DoComputeVerts(void);

        void setV(VectorTwo v);
        void setColour(ShapeColour colour);
        void setFillColour(ShapeColour colour);
        ShapeColour getColour();
        ShapeColour getFillColour();
        };
}

#endif