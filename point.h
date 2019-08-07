#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <math.h>

using namespace std;

template <class T>
class Point
{
    private:
        T xval, yval;
    public:
        // Constructor uses default arguments to allow calling with zero, one,
        // or two values.
        Point(T x, T y)
        {
            xval = x;
            yval = y;
        }

        // Extractors.
        T x()
        {
            return xval;
        }
        T y()
        {
            return yval;
        }

        // Distance to another point.  Pythagorean thm.
        double dist(Point<T> other)
        {
            double xd = xval - other.xval;
            double yd = yval - other.yval;
            return sqrt(xd * xd + yd * yd);
        }

        // Add or subtract two points.
        Point<T> add(Point<T> b)
        {
            return Point(xval + b.xval, yval + b.yval);
        }

        Point<T> sub(Point<T> b)
        {
            return Point(xval - b.xval, yval - b.yval);
        }

        // Move the existing point.
        void move(T a, T b)
        {
            xval += a;
            yval += b;
        }

        // Print the point on the stream.  The class ostream is a base class
        // for output streams of various types.
        void print(ostream& strm)
        {
            strm << "(" << xval << "," << yval << ")";
        }

        bool operator==(const Point<T>& lhs)
        {
            return this->xval == lhs.xval && this->yval == lhs.yval;
        }
};

#endif // POINT_H
