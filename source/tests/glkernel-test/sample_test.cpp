
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

TEST_F(sample_test, multi_jittered_compile)
{
    auto fkernel2 = glkernel::kernel2{ 1 };

    glkernel::sample::multi_jittered(fkernel2);

    auto dkernel2 = glkernel::dkernel2{ 1 };

    glkernel::sample::multi_jittered(dkernel2);
}

TEST_F(sample_test, multi_jittered_index_stratum_correlation)
{
    auto kernel = glkernel::kernel2{ 2, 2 };

    glkernel::sample::multi_jittered(kernel);

    ASSERT_LE(0.0f, kernel.value(0, 0).x);
    ASSERT_GE(0.5f, kernel.value(0, 0).x);
    ASSERT_LE(0.0f, kernel.value(0, 0).y);
    ASSERT_GE(0.5f, kernel.value(0, 0).y);

    ASSERT_LE(0.0f, kernel.value(0, 1).x);
    ASSERT_GE(0.5f, kernel.value(0, 1).x);
    ASSERT_LE(0.5f, kernel.value(0, 1).y);
    ASSERT_GE(1.0f, kernel.value(0, 1).y);

    ASSERT_LE(0.5f, kernel.value(1, 0).x);
    ASSERT_GE(1.0f, kernel.value(1, 0).x);
    ASSERT_LE(0.0f, kernel.value(1, 0).y);
    ASSERT_GE(0.5f, kernel.value(1, 0).y);

    ASSERT_LE(0.5f, kernel.value(1, 1).x);
    ASSERT_GE(1.0f, kernel.value(1, 1).x);
    ASSERT_LE(0.5f, kernel.value(1, 1).y);
    ASSERT_GE(1.0f, kernel.value(1, 1).y);
}

TEST_F(sample_test, multi_jittered_one_sample_per_stratum)
{
    auto kernel = glkernel::kernel2{ 5, 3 };
 
    glkernel::sample::multi_jittered(kernel);
    // check if exactly one sample is in the upper left stratum
    unsigned int count = 0;
    for (size_t i = 0; i < kernel.size(); ++i)
    {
        auto sample = kernel[i];
        if (0.f <= sample.x && sample.x < 1.f / 5.f && 0.f <= sample.y && sample.y < 1.f / 3.f)
        {
            ++count;
        }
    }
    ASSERT_EQ(1, count);
}

TEST_F(sample_test, multi_jittered_one_sample_per_column)
{
    auto kernel = glkernel::dkernel2{ 10, 10 };

    glkernel::sample::multi_jittered(kernel);

    // test if first column contains one sample
    unsigned int count = 0;
    for (size_t i = 0; i < kernel.size(); ++i)
    {
        auto &sample = kernel[i];
        if (0.0 <= sample.x && sample.x < 1.0 / (10.0 * 10.0))
        {
            ++count;
        }
    }
    ASSERT_EQ(1, count);
}

TEST_F(sample_test, multi_jittered_one_sample_per_row)
{
    auto kernel = glkernel::dkernel2{ 10, 10 };

    glkernel::sample::multi_jittered(kernel);

    // test if first row contains one sample
    unsigned int count = 0;
    for (size_t i = 0; i < kernel.size(); ++i)
    {
        auto &sample = kernel[i];
        if (0.0 <= sample.y && sample.y < 1.0 / (10.0 * 10.0))
        {
            ++count;
        }
    }
    ASSERT_EQ(1, count);
}

TEST_F(sample_test, multi_jittered_correlated_same_x_coord_for_row)
{
    auto kernel = glkernel::dkernel2{ 10, 10 };

    glkernel::sample::multi_jittered(kernel, true);

    // test if first row contains one sample
    auto base_sample = kernel.value(0, 0);
    for (glm::uint16 x = 1; x < kernel.width(); ++x)
    {
        auto &sample = kernel.value(x, 0);
        EXPECT_NEAR(sample.x - x * 0.1, base_sample.x, 0.01);
    }
}

TEST_F(sample_test, multi_jittered_correlated_same_y_coord_for_column)
{
    auto kernel = glkernel::dkernel2{ 10, 10 };

    glkernel::sample::multi_jittered(kernel, true);

    // test if first row contains one sample
    auto base_sample = kernel.value(0, 0);
    for (glm::uint16 y = 1; y < kernel.width(); ++y)
    {
        auto &sample = kernel.value(0, y);
        EXPECT_NEAR(sample.y - y * 0.1, base_sample.y, 0.01);
    }
}
