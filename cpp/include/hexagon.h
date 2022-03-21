#ifndef HEXAGON_LIBRARY_H
#define HEXAGON_LIBRARY_H

#include <cmath>
#include <iostream>
#include <vector>
#include <array>

struct Hexagon{
        int a = 0, b = 0;

        Hexagon& operator+=(Hexagon other)
        {
                a += other.a; 
                b += other.b;
                return *this;
        }
        Hexagon& operator-=(Hexagon other)
        {
                a -= other.a; 
                b -= other.b;
                return *this;
        }
        Hexagon& operator*=(int s)
        {
                a *= s; 
                b *= s;
                return *this;
        }
        Hexagon& operator/=(int s)
        {
                a /= s; 
                b /= s;
                return *this;
        }
};

inline bool operator==(Hexagon a, Hexagon b)
{
        return (a.a == b.a && a.b == b.b);
}
inline bool operator!=(Hexagon a, Hexagon b)
{
        return !(a == b);
}

#endif //HEXAGON_LIBRARY_H
