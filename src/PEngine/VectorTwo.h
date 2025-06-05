#include <ostream>
#ifndef VECTORTWO_H
#define VECTORTWO_H

namespace PEngine
{

    // Vector class for a a 2d physics vector.
    class VectorTwo
    {
    private:
        double x_ = 0;
        double y_ = 0;

    public:
        // ctor dtor
        VectorTwo();
        VectorTwo(double x, double y);
        VectorTwo(VectorTwo &other);

        ~VectorTwo();

        // static methods
        static VectorTwo Normalise(const VectorTwo &v);
        static double Dot(const VectorTwo &v1, const VectorTwo &v2);
        static double Cross(const VectorTwo &v1, const VectorTwo &v2);
        static double Length(const VectorTwo &v1);
        static double Distance(const VectorTwo &a, const VectorTwo &b);
        // getters
        double getX(void) const;
        double getY(void) const;

        // operator overloads
        VectorTwo &operator+=(const VectorTwo &other);
        VectorTwo &operator-=(const VectorTwo &other);
        VectorTwo &operator=(const VectorTwo &other);
        VectorTwo &operator*=(const double m);
        VectorTwo &operator/=(const double m);
        VectorTwo operator-();
        bool operator==(const VectorTwo &other) const;

        // friend operator overloads
        friend VectorTwo operator+(const VectorTwo &v1, const VectorTwo &v2);
        friend VectorTwo operator-(const VectorTwo &v1, const VectorTwo &v2);
        friend VectorTwo operator*(const VectorTwo &v, const double m);
        friend VectorTwo operator/(const VectorTwo &v, const double m);
        friend std::ostream &operator<<(std::ostream &stream, const VectorTwo &v);
    };
}

#endif
