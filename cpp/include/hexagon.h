#ifndef HEXAGON_LIBRARY_H
#define HEXAGON_LIBRARY_H

#include <cmath>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#include <point.h>
#include <edge.h>

namespace Hex{
struct Hexagon;
Point point_from_hex(Hexagon hex);

/*!*****************************************************************************
 * \defgroup Hex Hexagon
 * @{
 ******************************************************************************/
/*!*****************************************************************************
 * Basic structure for the hexagon, using hexagonal (non-orthogonal) 
 * lattice vectors \f$ \hat{a} = \hat{x}\f$ and \f$ \hat{b} = 
 * -\frac{1}{2}\hat{x} + \frac{\sqrt{3}}{2}\hat{y}\f$. The hexagon is 
 *  represented as a linear combination of these basis vectors, 
 *  \f$ \bar{a} + \bar{b} = a\hat{a} + b\hat{b} \f$, the integer coefficients
 *  are stored in the a and b member fields. Thus, the Hexagon center is given 
 *  as \f$(a, b)\f$ in the hexagonal basis.
 * The transformation matrix from ordinary cartesian (x, y) to our hexagonal 
 * coordinates (a, b) is given by the matrix trasformation matrix \f$
 * \mathbf{T}\f$ (Note that the hexagonal basis vectors form the columns of 
 * this matrix):
 * \f[
 * \mathbf{T} = \begin{bmatrix}
 * 1 & -\frac{1}{2}\\
 * 0 & \frac{\sqrt{3}}{2}\\
 * \end{bmatrix}.
 * \f]
 * Another way to say this is that:
 * \f[
 * \begin{bmatrix}
 * x\\
 * y
 * \end{bmatrix}
  = \mathbf{T}\begin{bmatrix}
  a\\
  b\\
  \end{bmatrix} = 
  \begin{bmatrix}
 * a - \frac{b}{2}\\
 * \frac{\sqrt{3}}{2}b
 * \end{bmatrix}.
 * \f]
 * As stated above, the hexagonal basis vectors are not orthogonal (but they 
 * are normalized, \f$|\hat{a}| = |\hat{b}| = 1 \f$), i.e. the inner product 
 * between them is nonzero.
 * \f[
 *      \left( \hat{a} \left| \hat{b}\right. \right) = 
 *      \left( \hat{x} \left| -\frac{\hat{x}}{2} + \frac{\sqrt{3}}{2}\hat{y} 
 *      \right.\right) = -\frac{1}{2}\left( \hat{x} \left| \right.\hat{x} 
 *      \right) + \frac{\sqrt{3}}{2} \left( \hat{x} \left| \hat{y} \right. 
 *      \right) = -\frac{1}{2},
 * \f]
 * actually, the angle between \f$ \hat{a} \f$ and \f$ \hat{b} \f$ is 
 * \f$ \frac{4\pi}{2} \f$ radians (or \f$120^{\circ}\f$).
 * NOTE:
 * In general a and b are real numbers, not necessarily integers. This class is 
 * only for integer coordinates (a, b).
*******************************************************************************/
struct Hexagon{
        int a, b;

        /*!*********************************************************************
         * A Hexagon Wedge is formed by three points; the center and two 
         * adjacent corners.
         **********************************************************************/
        using Wedge = std::array<Point, 3>;

        /*!*****************************************************************************
         * Return the Point corresponding to the center of the Hexagon.
         ******************************************************************************/
        Point to_point() const
        {
                using std::sqrt;
                return {this->a - this->b/2., sqrt(3.)/2.*this->b};
        }

        /*!*********************************************************************
         * Return a std::array<Point, 6> containing the 6 corners of the
         * Hexagon. Starting with the corner \f$ \frac{\pi}{6} \f$ radians above
         * the a-axis and going counter-clockwise (positive direction).
         **********************************************************************/
        std::array<Point, 6> corners() const
        {
                using std::sqrt;
                const Point center = this->to_point();
                return {center + Point{ 0.5,  1./(2*sqrt(3))},
                        center + Point{ 0  ,  1./sqrt(3)    },
                        center + Point{-0.5,  1./(2*sqrt(3))},
                        center + Point{-0.5, -1./(2*sqrt(3))},
                        center + Point{ 0  , -1./sqrt(3)    },
                        center + Point{ 0.5, -1/(2*sqrt(3)) }};
        }

        /*!*********************************************************************
         * Return a std::array<Wedge, 6> containing the 6 wedges of the
         * Hexagon. Starting with the one formed by the points 
         * [center, corners[0], corners[1]] and proceeding counter-clockwise (
         * positive direction).
         **********************************************************************/
        std::array<Wedge, 6> wedges() const
        {
                using std::sqrt;
                const Point center = this->to_point();
                const auto corners = this->corners();
                return {Wedge{center, corners[0], corners[1]},
                             {center, corners[1], corners[2]},
                             {center, corners[2], corners[3]},
                             {center, corners[3], corners[4]},
                             {center, corners[4], corners[5]},
                             {center, corners[5], corners[0]}};
        }

        /*!*********************************************************************
         * Return a std::array<Edge, 6> containing the 6 edges of the
         * Hexagon. Starting with the edge [corners[0], corners[1]], and going
         * counter-clockwise (positive direction), ending with the edge 
         * connecting the last corner to the first.
         **********************************************************************/
        std::array<Edge, 6> edges() const
        {
                std::array<Edge, 6> res;
                std::array<Point, 6> corners = this->corners();
                std::transform(std::begin(corners), std::end(corners) - 1, 
                               std::begin(corners) + 1, 
                               std::begin(res), 
                               [](Point start, Point stop)
                               {
                                        return Edge{start, stop};
                               });
                res[5] = Edge{corners.back(), corners.front()};
                return res;
        }

        /*!*********************************************************************
         * Component-wise addition assignment of the hexagonal coordinates.
         **********************************************************************/
        Hexagon& operator+=(Hexagon other)
        {
                a += other.a; 
                b += other.b;
                return *this;
        }

        /*!*********************************************************************
         * Component-wise subtraction assignment of the hexagonal coordinates.
         **********************************************************************/
        Hexagon& operator-=(Hexagon other)
        {
                a -= other.a; 
                b -= other.b;
                return *this;
        }

        /*!*********************************************************************
         * Component-wise multiplication assignment of the hexagonal 
         * coordinates.
         **********************************************************************/
        Hexagon& operator*=(Hexagon other)
        {
                a *= other.a; 
                b *= other.b;
                return *this;
        }

        /*!*********************************************************************
         * Component-wise division assignment of the hexagonal coordinates.
         **********************************************************************/
        Hexagon& operator/=(Hexagon other)
        {
                a /= other.a; 
                b /= other.b;
                return *this;
        }

        /*!*********************************************************************
         * Component-wise scaling  assignment of the hexagonal coordinates.
         **********************************************************************/
        Hexagon& operator*=(int s)
        {
                a *= s; 
                b *= s;
                return *this;
        }

        /*!*********************************************************************
         * Component-wise scaling  assignment of the hexagonal coordinates.
         **********************************************************************/
        Hexagon& operator/=(int s)
        {
                a /= s; 
                b /= s;
                return *this;
        }

        /*!*********************************************************************
         * Return the string "Hexagon(a_, b_)" with a_ and b_ replaced by the a 
         * and b coordinates respectively.
         **********************************************************************/
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


/*!*****************************************************************************
 * Rotate the target Hexagon \f$ \frac{\pi}{3} \f$ radians counter-clockwise 
 * (positive direction).
 ******************************************************************************/
inline Hexagon rotate(Hexagon a)
{
        return {a.a - a.b, a.a};
}

/*!*****************************************************************************
 * Rotate the target Hexagon \f$ \frac{\pi}{3} \f$ radians clockwise 
 * (negative direction).
 ******************************************************************************/
inline Hexagon rotate_clockwise(Hexagon a)
{
        return {a.b, -a.a + a.b};
}

/*!*****************************************************************************
 * Rotate the target Hexagon theta radians counter-clockwise (positive 
 * direction).
 ******************************************************************************/
inline Hexagon rotate(Hexagon a, double theta)
{
        double sin = std::sin(theta), cos = std::cos(theta), ist = 1./std::sqrt(3);
        return {static_cast<int>(std::round(a.a*cos + ist*(a.a - 2*a.b)*sin)),
                static_cast<int>(std::round(a.b*cos - ist*(a.b - 2*a.a)*sin))};
}

/*!*****************************************************************************
 * Rotate the target Hexagon theta radians clockwise (negative direction).
 ******************************************************************************/
inline Hexagon rotate_clockwise(Hexagon a, double theta)
{
        return rotate(a, -theta);
}

/*!*****************************************************************************
 * Calculate the Manhatan distance (sum of number of hexes moved along a and b)
 * to reach the Hexagon hex, 
 * \f$\frac{1}{2} \left( |a| + |b| + |a - b| \right) \f$.
 * Note that since we are using a non-orthogonal basis this is not just the sum
 * of the absolute values of the \f$\hat{a}\f$ and \f$\hat{b}\f$ components.)
 ******************************************************************************/
inline int manhattan_distance(Hexagon hex)
{
        using std::abs;
        return (abs(hex.a) + abs(hex.a - hex.b) + abs(hex.b))/2;
}

/*!*****************************************************************************
 * Calculate the Euclidean distance of the hexagon hex.
 * \f[
 * \sqrt{\left( \bar{a} + \bar{b} \left| \bar{a} + \bar{b} \right.\right)} = 
 * \sqrt{a^2 \left( \hat{a} \left| \hat{a} \right.\right) + 
 *       b^2 \left( \hat{b} \left| \hat{b} \right.\right) + 
 *       2ab \left( \hat{a} \left| \hat{b} \right.\right)} = 
 *      \sqrt{a^2 + b^2 - ab}.
 * \f]
 ******************************************************************************/
inline double euclidean_distance(Hexagon hex)
{
        using std::sqrt; using std::abs;
        return sqrt(hex.a*hex.a + hex.b*hex.b - hex.a*hex.b);
}

static const std::array<Hexagon, 6> neighbor_directions {
        Hexagon{1, 0}, Hexagon{1, 1}, Hexagon{0, 1}, 
        Hexagon{-1, 0}, Hexagon{-1, -1}, Hexagon{0, -1}
};

/*!*****************************************************************************
 * Return a std::vector<Hexagon> containing all hexagons at radius steps away 
 * from center, the order is counter-clockise starting from the Hexagon in the 
 * (-1, -1) direction.
 ******************************************************************************/
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

/*!*****************************************************************************
 * Return a std::vector<Hexagon> containing all hexagons inside radius steps 
 * away from center, the order is counter-clockise starting from the Hexagon in 
 * the (-1, -1) direction (except the first hexagon is center).
 ******************************************************************************/
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

/*!*****************************************************************************
 * Find the Hexagon center closest to the cartesian point (x, y). Note that all
 * Hexagons have integer coordinates, thus the need for rounding the 
 * hexagonal coordinates.
 ******************************************************************************/
inline Hexagon nearest_hex(Point p)
{
        using std::round; using std::sqrt; using std::abs;
        const double a = p.x + 1./sqrt(3.)*p.y, b = 2./sqrt(3.)*p.y;
        const double c = b - a;
        int rounded_a = static_cast<int>(round(a));
        int rounded_b = static_cast<int>(round(b));
        int rounded_c = static_cast<int>(round(c));

        /***********************************************************************
         * da measures how far rounding has moved us along the a direction, and
         * db measures how far we have moved along the b direction.
         * There is however the possibility that we should look at how far we
         * have moved along the "diagonal" b - a direction, I call this direction c and the
         * corresponding quantity dc.
         *   b
         *   \\
         *     \\
         *       \\
         *          ======= a
         **********************************************************************/
        const double da = abs(a - rounded_a), db = abs(b - rounded_b);
        const double dc = abs(c - rounded_c);
        
        /***********************************************************************
         * If we have moved the most along a, keep the b and "c" components 
         * fixed and update the a component to match them. a = -b - c.
         **********************************************************************/
        if(da > db && da > dc){
                rounded_a = -rounded_b - rounded_c;
        /***********************************************************************
         * If we have moved the most along b, keep the a and "c" components 
         * fixed and update the b component to match them. b = -a - c.
         **********************************************************************/
        }else if(db > dc){
                rounded_b = -rounded_a - rounded_c;
        }
        /***********************************************************************
         * If we have moved the most along "c", we should keep a and b constant,
         * aaand that's it, no need to update the fictitious "c" coordinate.
         * If our movements along a, b and c are all equal, we chose to do 
         * nothing, because we have to chose something.
         **********************************************************************/
        
        return Hexagon{rounded_a, rounded_b};
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
}
#endif //HEXAGON_LIBRARY_H
