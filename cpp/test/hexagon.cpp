#include <gtest/gtest.h>
#include <hexagon.h>

using namespace Hex;

TEST(Hexagon, Equality)
{
        Hexagon h1, h2{0, 0};
        ASSERT_EQ(h1, h2);
}

TEST(Hexagon, Inequality)
{
        Hexagon h1, h2{1, 1};
        ASSERT_NE(h1, h2);
}

TEST(Hexagon, Increment)
{
        Hexagon h1, h2{1, 2};
        h1 += h2;
        ASSERT_EQ(h1, h2);
}

TEST(Hexagon, Decrement)
{
        Hexagon h1, h2{1, 2};
        h1 -= h2;
        ASSERT_EQ(h1, -h2);
}

TEST(Hexagon, ScaleMult)
{
        Hexagon h1{1, 2}, h2{2, 4};
        int s = 2;
        h1 *= s;
        ASSERT_EQ(h1, h2);
}

TEST(Hexagon, ScaleDiv)
{
        Hexagon h1{2, 4}, h2{1, 2};
        int s = 2;
        h1 /= s;
        ASSERT_EQ(h1, h2);
}

TEST(Hexagon, Negate)
{
        Hexagon h1{1, 2}, h2{-1, -2};
        ASSERT_EQ(-h1, h2);
}

TEST(Hexagon, Addition)
{
        Hexagon h1, h2{1, 2};
        ASSERT_EQ(h1 + h2, h2);
}

TEST(Hexagon, Subtraction)
{
        Hexagon h1, h2{1, 2};
        h1 -= h2;
        ASSERT_EQ(h1, -h2);
}

TEST(Hexagon, Multiplication)
{
        Hexagon h1{1, 2}, h2{2, 4};
        ASSERT_EQ(h1*2, h2);
}

TEST(Hexagon, Division) 
{
        Hexagon h1{2, 4}, h2{1, 2};
        ASSERT_EQ(h1/2, h2);
}

TEST(Hexagon, Rotate60)
{
        Hexagon h1{1, 0}, h2{1, 1};
        ASSERT_EQ(rotate(h1), h2);
}

TEST(Hexagon, RotateCounterClockwise60)
{
        Hexagon h1{1, 0}, h2{0, -1};
        ASSERT_EQ(rotate_clockwise(h1), h2);
}

TEST(Hexagon, Rotate120)
{
        Hexagon h1{1, 0}, h2{0, 1};
        ASSERT_EQ(rotate(h1, 120/180.*M_PI), h2);
}

TEST(Hexagon, RotateCounterClockwise120)
{
        Hexagon h1{1, 0}, h2{-1, -1};
        std::cout << rotate_clockwise(h1, 120/180.*M_PI) << "\n";
        ASSERT_EQ(rotate_clockwise(h1, 120/180.*M_PI), h2);
}

TEST(Hexagon, RotateAndRotateBack)
{
        Hexagon h1{1, 0};
        ASSERT_EQ(rotate(rotate_clockwise(h1)), h1);
}

TEST(Hexagon, ManhattanDistance)
{
        Hexagon h1{2, 3};
        ASSERT_EQ(manhattan_distance(h1), 3);
}

TEST(Hexagon, EuclideanDistance)
{
        Hexagon h1{2, 3};
        ASSERT_EQ(euclidean_distance(h1), std::sqrt(7));
}

TEST(Hexagon, Ring)
{
        Hexagon h1{0, 0};
        std::vector<Hexagon> answer = {{-1, -1}, {0, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 0}};
        ASSERT_EQ(ring(h1, 1), answer);
}

TEST(Hexagon, RingRadius0)
{
        Hexagon h1{0, 0};
        std::vector<Hexagon> answer = {h1};
        ASSERT_EQ(ring(h1, 0), answer);
}

TEST(Hexagon, Spiral)
{
        Hexagon h1{0, 0};
        std::vector<Hexagon> answer = {{0, 0}, {-1, -1}, {0, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 0}};
        ASSERT_EQ(spiral(h1, 1), answer);
}

TEST(Hexagon, CartesianToHex)
{
        Hexagon h1{1, 0};
        Point p1{0.5, 0};
        Hexagon h2{0, 0};
        Point p2{0, 0.5};
        ASSERT_EQ(nearest_hex(p1), h1);
        ASSERT_EQ(nearest_hex(p2), h2);
}

TEST(Hexagon, ToString)
{
        Hexagon h1{1, 2};
        ASSERT_EQ(h1.to_string(), "Hexagon(1, 2)");
}

TEST(Hexagon, ToPoint)
{
        Hexagon h{1, 2};
        Point p{0, std::sqrt(3)};
        ASSERT_EQ(h.to_point(), p);
}

TEST(Hexagon, Corners)
{
        const double sq3 = std::sqrt(3);
        Hexagon h{1, 2};
        auto corners = h.corners();
        std::array<Point, 6> answer{
                Point{ 0.5, sq3 + 1./(2*sq3)},
                Point{ 0  , sq3 + 1./sq3    },
                Point{-0.5, sq3 + 1./(2*sq3)},
                Point{-0.5, sq3 - 1./(2*sq3)},
                Point{ 0  , sq3 - 1./sq3    },
                Point{ 0.5, sq3 - 1./(2*sq3)},
        };
        ASSERT_EQ(corners, answer);
}

TEST(Hexagon, Edges)
{
        Hexagon h{1, 2};
        const auto corners = h.corners();
        std::array<Edge, 6> answer {
                Edge{corners[0], corners[1]},
                Edge{corners[1], corners[2]},
                Edge{corners[2], corners[3]},
                Edge{corners[3], corners[4]},
                Edge{corners[4], corners[5]},
                Edge{corners[5], corners[0]},
        };
        const auto edges = h.edges();
        ASSERT_EQ(edges, answer);
}

TEST(Hexagon, Wedges)
{
        Hexagon h{1, 2};
        const auto corners = h.corners();
        const auto center = h.to_point();
        std::array<Hexagon::Wedge, 6> answer {
                Hexagon:: Wedge{center, corners[0], corners[1]},
                               {center, corners[1], corners[2]},
                               {center, corners[2], corners[3]},
                               {center, corners[3], corners[4]},
                               {center, corners[4], corners[5]},
                               {center, corners[5], corners[0]},
        };
        const auto wedges = h.wedges();
        ASSERT_EQ(wedges, answer);
}

