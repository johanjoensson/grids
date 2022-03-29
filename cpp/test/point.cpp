#include <gtest/gtest.h>
#include <point.h>

using namespace Hex;

TEST(Point, Equality)
{
        Point p1, p2{0, 0};
        ASSERT_EQ(p1, p2);
}

TEST(Point, Inequality)
{
        Point p1, p2{1, 1};
        ASSERT_NE(p1, p2);
}

TEST(Point, Increment)
{
        Point p1, p2{1, 2};
        p1 += p2;
        ASSERT_EQ(p1, p2);
}

TEST(Point, Decrement)
{
        Point p1, p2{1, 2};
        p1 -= p2;
        ASSERT_EQ(p1, -p2);
}

TEST(Point, ScaleMult)
{
        Point p1{1, 2}, p2{2, 4};
        int s = 2;
        p1 *= s;
        ASSERT_EQ(p1, p2);
}

TEST(Point, ScaleDiv)
{
        Point p1{2, 4}, p2{1, 2};
        int s = 2;
        p1 /= s;
        ASSERT_EQ(p1, p2);
}

TEST(Point, Negate)
{
        Point p1{1, 2}, p2{-1, -2};
        ASSERT_EQ(-p1, p2);
}

TEST(Point, Addition)
{
        Point p1, p2{1, 2};
        ASSERT_EQ(p1 + p2, p2);
}

TEST(Point, Subtraction)
{
        Point p1, p2{1, 2};
        p1 -= p2;
        ASSERT_EQ(p1, -p2);
}

TEST(Point, Multiplication)
{
        Point p1{1, 2}, p2{2, 4};
        ASSERT_EQ(p1*2, p2);
}

TEST(Point, Division) 
{
        Point p1{2, 4}, p2{1, 2};
        ASSERT_EQ(p1/2, p2);
}

TEST(Point, ToString)
{
        Point p1{1, 2};
        /*
         * THIS TEST IS SHAKY AS F*CK
         */
        ASSERT_EQ(p1.to_string(), "Point(1.000000, 2.000000)");
}
