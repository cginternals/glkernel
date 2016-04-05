
#include <gmock/gmock.h>


#include <glm/vec2.hpp>

#include <glkernel/Kernel.h>
#include <glkernel/scale.h>


class scale_test: public testing::Test
{
public:
};

TEST_F(scale_test, range_compile)
{
    auto fkernel2 = glkernel::kernel2{ 8, 8, 8 };
    glkernel::scale::range(fkernel2, -0.5f, 0.5f);
}

TEST_F(scale_test, range)
{
    auto fkernel2 = glkernel::kernel2{ 2, 2 };
    fkernel2[0] = {6, 7};
    fkernel2[1] = {5, 9};
    fkernel2[2] = {10, 8};
    fkernel2[3] = {7, 9};
    glkernel::scale::range(fkernel2, -0.5f, 0.5f, 5.f, 10.f);

    EXPECT_FLOAT_EQ(-.3f, fkernel2[0][0]);
    EXPECT_FLOAT_EQ(-.1f, fkernel2[0][1]);
    EXPECT_FLOAT_EQ(-.5f, fkernel2[1][0]);
    EXPECT_FLOAT_EQ(.3f, fkernel2[1][1]);
    EXPECT_FLOAT_EQ(.5f, fkernel2[2][0]);
    EXPECT_FLOAT_EQ(.1f, fkernel2[2][1]);
    EXPECT_FLOAT_EQ(-.1f, fkernel2[3][0]);
    EXPECT_FLOAT_EQ(.3f, fkernel2[3][1]);
}
