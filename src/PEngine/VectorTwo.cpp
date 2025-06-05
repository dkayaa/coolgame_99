#include "VectorTwo.h"
#include <cmath>

namespace PEngine
{

    VectorTwo::VectorTwo() {};

    VectorTwo::VectorTwo(double x, double y)
    {
        x_ = x;
        y_ = y;
    }

    VectorTwo::VectorTwo(VectorTwo &other)
    {
        x_ = other.getX();
        y_ = other.getY();
    }
    VectorTwo::~VectorTwo() {};

    // static methods
    VectorTwo VectorTwo::Normalise(const VectorTwo &v)
    {
        double x = v.getX();
        double y = v.getY();
        double l = Length(v);
        return VectorTwo(x / l, y / l);
    }

    double VectorTwo::Dot(const VectorTwo &v1, const VectorTwo &v2)
    {
        // Dot(A, B) = A^T B
        double ax = v1.getX();
        double ay = v1.getY();
        double bx = v2.getX();
        double by = v2.getY();

        return ax * bx + ay * by;
    }
    double VectorTwo::Cross(const VectorTwo &a, const VectorTwo &b)
    {
        return a.getX() * b.getY() - b.getX() * a.getY();
    }

    double VectorTwo::Distance(const VectorTwo &a, const VectorTwo &b)
    {
        return Length(b - a);
    }

    double VectorTwo::Length(const VectorTwo &v)
    {
        return sqrt(pow(v.getX(), 2) + pow(v.getY(), 2));
    }

    // getters
    double VectorTwo::getX(void) const
    {
        return x_;
    }
    double VectorTwo::getY(void) const
    {
        return y_;
    }

    // operator overloads
    VectorTwo &VectorTwo::operator+=(const VectorTwo &other)
    {
        (*this).x_ += other.getX();
        (*this).y_ += other.getY();
        return *this;
    }
    VectorTwo &VectorTwo::operator-=(const VectorTwo &other)
    {
        return *this;
    }
    VectorTwo &VectorTwo::operator=(const VectorTwo &other)
    {
        (*this).x_ = other.x_;
        (*this).y_ = other.y_;
        return *this;
    }
    VectorTwo &VectorTwo::operator*=(const double m)
    {
        (*this).x_ *= m;
        (*this).y_ *= m;
        return *this;
    }
    VectorTwo &VectorTwo::operator/=(const double m)
    {
        (*this).x_ /= m;
        (*this).y_ /= m;
        return *this;
    }

    VectorTwo VectorTwo::operator-()
    {
        VectorTwo v = VectorTwo(-x_, -y_);
        return v;
    }
    bool VectorTwo::operator==(const VectorTwo &other) const
    {
        return ((other.getX() == (*this).getX()) && (other.getY() == (*this).getY()));
    }

    VectorTwo operator+(const VectorTwo &v1, const VectorTwo &v2)
    {
        double ax = v1.getX();
        double ay = v1.getY();
        double bx = v2.getX();
        double by = v2.getY();

        VectorTwo r = VectorTwo(ax + bx, ay + by);
        return r;
    }
    VectorTwo operator-(const VectorTwo &v1, const VectorTwo &v2)
    {
        double ax = v1.getX();
        double ay = v1.getY();
        double bx = v2.getX();
        double by = v2.getY();

        VectorTwo r = VectorTwo(ax - bx, ay - by);
        return r;
    }

    VectorTwo operator*(const VectorTwo &v, const double m)
    {
        return VectorTwo(v.getX() * m, v.getY() * m);
    }

    VectorTwo operator/(const VectorTwo &v, const double m)
    {
        return VectorTwo(v.getX() / m, v.getY() / m);
    }

    std::ostream &operator<<(std::ostream &stream, const VectorTwo &v)
    {
        stream << "X: " << v.getX() << ", Y: " << v.getY() << ", L: " << VectorTwo::Length(v);
        return stream;
    }
}
