
#include <gmock/gmock.h>


#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glkernel/Kernel.h>
#include <glkernel/sample.h>


class sample_test: public testing::Test
 {
 public:
 };

TEST_F(sample_test, poisson_square_compile)
{
    auto fkernel2 = glkernel::kernel2{ 1 };

    glkernel::sample::poisson_square(fkernel2);

    auto dkernel2 = glkernel::dkernel2{ 1 };

    glkernel::sample::poisson_square(dkernel2);
}

TEST_F(sample_test, hammersley_compile)
{
    auto fkernel2 = glkernel::kernel2{ 1 };

    glkernel::sample::hammersley(fkernel2);

    auto dkernel2 = glkernel::dkernel2{ 1 };

    glkernel::sample::hammersley(dkernel2);
}

TEST_F(sample_test, hammersley_sphere_compile)
{
    auto fkernel3 = glkernel::kernel3{ 1 };

    glkernel::sample::hammersley_sphere(fkernel3);

    auto dkernel3 = glkernel::dkernel3{ 1 };

    glkernel::sample::hammersley_sphere(dkernel3);
}

TEST_F(sample_test, hammersley)
{
    auto kernel = glkernel::kernel2{ 2, 2 };

    glkernel::sample::hammersley(kernel);

    EXPECT_FLOAT_EQ(0.0f / 4.0f, kernel[0].x);
    EXPECT_FLOAT_EQ(0.0f, kernel[0].y);

    EXPECT_FLOAT_EQ(1.0f / 4.0f, kernel[1].x);
    EXPECT_FLOAT_EQ(1.0f / 2.0f, kernel[1].y);

    EXPECT_FLOAT_EQ(2.0f / 4.0f, kernel[2].x);
    EXPECT_FLOAT_EQ(1.0f / 4.0f, kernel[2].y);

    EXPECT_FLOAT_EQ(3.0f / 4.0f, kernel[3].x);
    EXPECT_FLOAT_EQ(3.0f / 4.0f, kernel[3].y);
}

TEST_F(sample_test, halton_compile)
{
    auto fkernel2 = glkernel::kernel2{ 1 };

    glkernel::sample::halton(fkernel2, 2, 3);

    auto dkernel2 = glkernel::dkernel2{ 1 };

    glkernel::sample::halton(dkernel2, 2, 3);
}

TEST_F(sample_test, halton_sphere_compile)
{
    auto fkernel3 = glkernel::kernel3{ 1 };

    glkernel::sample::halton_sphere(fkernel3, 2, 3);

    auto dkernel3 = glkernel::dkernel3{ 1 };

    glkernel::sample::halton_sphere(dkernel3, 2, 3);
}

TEST_F(sample_test, halton)
{
    auto kernel = glkernel::kernel2{ 2, 2 };

    glkernel::sample::halton(kernel, 2, 3);

    EXPECT_FLOAT_EQ(0.0f, kernel[0].x);
    EXPECT_FLOAT_EQ(0.0f, kernel[0].y);

    EXPECT_FLOAT_EQ(1.0f / 2.0f, kernel[1].x);
    EXPECT_FLOAT_EQ(1.0f / 3.0f, kernel[1].y);

    EXPECT_FLOAT_EQ(1.0f / 4.0f, kernel[2].x);
    EXPECT_FLOAT_EQ(2.0f / 3.0f, kernel[2].y);

    EXPECT_FLOAT_EQ(3.0f / 4.0f, kernel[3].x);
    EXPECT_FLOAT_EQ(1.0f / 9.0f, kernel[3].y);
}
