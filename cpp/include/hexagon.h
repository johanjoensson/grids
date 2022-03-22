#ifndef HEXAGON_LIBRARY_H
#define HEXAGON_LIBRARY_H

#include <cmath>
#include <iostream>
#include <vector>
#include <array>

/*!*****************************************************************************
 * \defgroup Hex Hexagon
 * @{
 ******************************************************************************/
/*!*****************************************************************************
 * Basic structure for the hexagon. We are using hexagonal (non-orthogonal) 
 * lattice coordinates, i.e.(a|b) = -0.5, where (a|b) denotes the dot product of 
 * a and b.
*******************************************************************************/
struct Hexagon{
        int a, b;

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

        std::string to_string() const
        {
                using std::to_string;
                return "Hexagon(" + to_string(a) + ", " + to_string(b) + ")";
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

inline Hexagon operator-(Hexagon a)
{
        return {-a.a, -a.b};
}
inline Hexagon operator+(Hexagon a, Hexagon b)
{
        return a += b;
}

inline Hexagon operator-(Hexagon a, Hexagon b)
{
        return a -= b;
}

inline Hexagon operator*(Hexagon a, int s)
{
        return a *= s;
}

inline Hexagon operator*(int s, Hexagon a)
{
        return a*s;
}

inline Hexagon operator/(Hexagon a, int s)
{
        return a /= s;
}

inline Hexagon rotate(Hexagon a)
{
        return {a.a - a.b, a.a};
}

inline Hexagon rotate_clockwise(Hexagon a)
{
        return {a.b, -a.a + a.b};
}

inline Hexagon rotate(Hexagon a, double theta)
{
        double sin = std::sin(theta), cos = std::cos(theta), ist = 1./std::sqrt(3);
        return {static_cast<int>(std::round(a.a*cos + ist*(a.a - 2*a.b)*sin)),
                static_cast<int>(std::round(a.b*cos - ist*(a.b - 2*a.a)*sin))};
}

inline Hexagon rotate_clockwise(Hexagon a, double theta)
{
        return rotate(a, -theta);
}

inline int manhattan_distance(Hexagon a)
{
        using std::abs;
        return (abs(a.a) + abs(a.a - a.b) + abs(a.b))/2;
}

inline double euclidean_distance(Hexagon a)
{
        return std::sqrt(a.a*a.a + a.b*a.b - a.a*a.b);
}

static const std::array<Hexagon, 6> neighbor_directions {
        Hexagon{1, 0}, Hexagon{1, 1}, Hexagon{0, 1}, 
        Hexagon{-1, 0}, Hexagon{-1, -1}, Hexagon{0, -1}
};

inline std::vector<Hexagon> ring(Hexagon center, int radius)
{
        if(radius == 0){
                return {center};
        }
        std::vector<Hexagon> res;
        res.reserve(6*radius);
        Hexagon current = center + radius*neighbor_directions[4];
        for(const auto& direction : neighbor_directions){
                for(int step = 0; step < radius; step++){
                        res.push_back(current);
                        current += direction;
                }
        }
        return res;
}

inline std::vector<Hexagon> spiral(Hexagon center, int radius)
{
        using std::make_move_iterator;
        std::vector<Hexagon> res;
        res.reserve(1 + 3*radius*(radius + 1));

       for(int r = 0; r <= radius; r++){
               auto current_ring = ring(center, r);
               res.insert(
                               res.end(), 
                               make_move_iterator(current_ring.begin()),
                               make_move_iterator(current_ring.end())
                         );
       }
       return res;
}

inline std::string to_string(Hexagon a)
{
        return a.to_string();
}

inline std::ostream& operator<<(std::ostream& os, Hexagon a)
{
        return os << a.to_string();
}
/*!*****************************************************************************
* @}
*******************************************************************************/
#endif //HEXAGON_LIBRARY_H
