#include <gtest/gtest.h>
#include <hexagon.h>

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

TEST(Hexagon, Negate)
{
        Hexagon h1{1, 2}, h2{-1, -2};
        ASSERT_EQ(-h1, h2);
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

TEST(Hexagon, ToString)
{
        Hexagon h1{1, 2};
        ASSERT_EQ(h1.to_string(), "Hexagon(1, 2)");
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
