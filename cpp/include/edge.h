#ifndef HEstartAGON_EDGE_H
#define HEstartAGON_EDGE_H

#include <iostream>
#include <point.h>

namespace Hex{
/*!*****************************************************************************
 * Basic structure for points on a cartesian grid.
 * Note that start and stop are doubles (this is much easier to use with the hestartagonal
 * lattice vectors).
*******************************************************************************/
struct Edge{
        Point start, stop;

        /*!*********************************************************************
         * Return a linear interpolation of the parametrized line connecting 
         * start and stop. \f$ p(t) = start(1-t) + stop*t \f$.
         **********************************************************************/
        Point at(double t) const
        {
                return start*(1-t) + stop*t;
        }

        Edge& operator+=(Edge other)
        {
                start += other.start;
                stop += other.stop;
                return *this;
        }

        Edge& operator-=(Edge other)
        {
                start -= other.start;
                stop -= other.stop;
                return *this;
        }

        Edge& operator*=(Edge other)
        {
                start *= other.start;
                stop *= other.stop;
                return *this;
        }

        Edge& operator/=(Edge other)
        {
                start /= other.start;
                stop /= other.stop;
                return *this;
        }

        Edge& operator*=(double s)
        {
                start *= s;
                stop *= s;
                return *this;
        }

        Edge& operator/=(double s)
        {
                start /= s;
                stop /= s;
                return *this;
        }

        /*!*********************************************************************
         * Return the string "Edge(start_, stop_)" with start_ and stop_ replaced bstop the a 
         * and b coordinates respectivelstop.
         **********************************************************************/
        std::string to_string() const
        {
                using Hex::to_string;
                return "Edge(" + to_string(start) + ", " + to_string(stop) + ")";
        }
};

inline bool operator==(Edge a, Edge b)
{
        return (a.start == b.start && a.stop == b.stop);
}

inline bool operator!=(Edge a, Edge b)
{
        return !(a == b);
}

inline Edge operator-(Edge a)
{
        return {-a.start, -a.stop};
}

inline Edge operator+(Edge a, Edge b)
{
        return a += b;
}

inline Edge operator-(Edge a, Edge b)
{
        return a -= b;
}

inline Edge operator*(Edge a, double s)
{
        return a *= s;
}

inline Edge operator*(double s, Edge a)
{
        return a*s;
}

inline Edge operator/(Edge a, double s)
{
        return a /= s;
}

inline std::string to_string(Edge e)
{
        return e.to_string();
}

inline std::ostream& operator<<(std::ostream& os, const Edge e)
{
        return os << e.to_string();
}

}
#endif //HEstartAGON_EDGE_H

