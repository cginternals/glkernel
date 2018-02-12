
#include <gmock/gmock.h>


#include <glm/vec2.hpp>

#include <glkernel/Kernel.h>
#include <glkernel/sort.h>


class sort_test: public testing::Test
{
public:
};

TEST_F(sort_test, distance_compile)
{
    auto fkernel2 = glkernel::kernel2{ 8, 8, 8 };
    glkernel::sort::distance(fkernel2, glm::vec2{0, 0});
}

TEST_F(sort_test, distance_sorted)
{
    auto fkernel2 = glkernel::kernel2{ 2, 2 };
    fkernel2[0] = {3, 3};
    fkernel2[1] = {1, 1};
    fkernel2[2] = {2, 0};
    fkernel2[3] = {-4, 0};
    glkernel::sort::distance(fkernel2, {0, 0});

    EXPECT_FLOAT_EQ(1.f, fkernel2[0][0]);
    EXPECT_FLOAT_EQ(1.f, fkernel2[0][1]);
    EXPECT_FLOAT_EQ(2.f, fkernel2[1][0]);
    EXPECT_FLOAT_EQ(0.f, fkernel2[1][1]);
    EXPECT_FLOAT_EQ(-4.f, fkernel2[2][0]);
    EXPECT_FLOAT_EQ(0.f, fkernel2[2][1]);
    EXPECT_FLOAT_EQ(3.f, fkernel2[3][0]);
    EXPECT_FLOAT_EQ(3.f, fkernel2[3][1]);
}
