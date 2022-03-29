#include <gtest/gtest.h>
#include <edge.h>

using namespace Hex;

TEST(Edge, Equality)
{
        Edge p1, p2{{0, 0}, {0, 0}};
        ASSERT_EQ(p1, p2);
}

TEST(Edge, Inequality)
{
        Edge p1, p2{{1, 1}, {0, 0}};
        ASSERT_NE(p1, p2);
}

TEST(Edge, ToString)
{
        Edge p1{{1, 2}, {0, 0}};
        /*
         * THIS TEST IS SHAKY AS F*CK
         */
        ASSERT_EQ(p1.to_string(), "Edge(Point(1.000000, 2.000000), Point(0.000000, 0.000000))");
}
