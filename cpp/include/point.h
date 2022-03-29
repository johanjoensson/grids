#ifndef HEXAGON_POINT_H
#define HEXAGON_POINT_H
#include <iostream>

namespace Hex{
/*!*****************************************************************************
 * Basic structure for points on a cartesian grid.
 * Note that x and y are doubles (this is much easier to use with the hexagonal
 * lattice vectors).
*******************************************************************************/
struct Point{
        double x, y;

        /*!*********************************************************************
         * Component-wise addition assignment of the cartesian coordinates.
         **********************************************************************/
        Point& operator+=(Point other)
        {
                x += other.x;
                y += other.y;
                return *this;
        }

        /*!*********************************************************************
         * Component-wise subtraction assignment of the cartesian coordinates.
         **********************************************************************/
        Point& operator-=(Point other)
        {
                x -= other.x;
                y -= other.y;
                return *this;
        }

        /*!*********************************************************************
         * Component-wise multiplication assignment of the cartesian 
         * coordinates.
         **********************************************************************/
        Point& operator*=(Point other)
        {
                x *= other.x;
                y *= other.y;
                return *this;
        }

        /*!*********************************************************************
         * Component-wise division assignment of the cartesian coordinates.
         **********************************************************************/
        Point& operator/=(Point other)
        {
                x /= other.x;
                y /= other.y;
                return *this;
        }

        /*!*********************************************************************
         * Component-wise scaling assignment of the cartesian coordinates.
         **********************************************************************/
        Point& operator*=(double s)
        {
                x *= s;
                y *= s;
                return *this;
        }

        /*!*********************************************************************
         * Component-wise scaling assignment of the cartesian coordinates.
         **********************************************************************/
        Point& operator/=(double s)
        {
                x /= s;
                y /= s;
                return *this;
        }

        /*!*********************************************************************
         * Return the string "Point(x_, y_)" with x_ and y_ replaced by the a 
         * and b coordinates respectively.
         **********************************************************************/
        std::string to_string() const
        {
                using std::to_string;
                return "Point(" + to_string(x) + ", " + to_string(y) + ")";
        }
};

inline bool operator==(Point a, Point b)
{
        return (a.x == b.x && a.y == b.y);
}

inline bool operator!=(Point a, Point b)
{
        return !(a == b);
}

inline Point operator-(Point a)
{
        return {-a.x, -a.y};
}

inline Point operator+(Point a, Point b)
{
        return a += b;
}

inline Point operator-(Point a, Point b)
{
        return a -= b;
}

inline Point operator*(Point a, double s)
{
        return a *= s;
}

inline Point operator*(double s, Point a)
{
        return a*s;
}

inline Point operator/(Point a, double s)
{
        return a /= s;
}

inline std::string to_string(Point p)
{
        return p.to_string();
}

inline std::ostream& operator<<(std::ostream& os, const Point p)
{
        return os << p.to_string();
}

}
#endif //HEXAGON_POINT_H
