#include <gtest/gtest.h>
#include <hexagon.h>

TEST(Hexagon, Equality)
{
        Hexagon h1;
        ASSERT_EQ(h1, Hexagon{});
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
