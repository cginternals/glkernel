
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
    auto fkernel2 = glkernel::kernel2{ 2, 2 };

    glkernel::sample::multi_jittered(fkernel2);

    ASSERT_LE(0.0f, fkernel2.value(0, 0).x);
    ASSERT_GE(0.5f, fkernel2.value(0, 0).x);
    ASSERT_LE(0.0f, fkernel2.value(0, 0).y);
    ASSERT_GE(0.5f, fkernel2.value(0, 0).y);

    ASSERT_LE(0.0f, fkernel2.value(0, 1).x);
    ASSERT_GE(0.5f, fkernel2.value(0, 1).x);
    ASSERT_LE(0.5f, fkernel2.value(0, 1).y);
    ASSERT_GE(1.0f, fkernel2.value(0, 1).y);

    ASSERT_LE(0.5f, fkernel2.value(1, 0).x);
    ASSERT_GE(1.0f, fkernel2.value(1, 0).x);
    ASSERT_LE(0.0f, fkernel2.value(1, 0).y);
    ASSERT_GE(0.5f, fkernel2.value(1, 0).y);

    ASSERT_LE(0.5f, fkernel2.value(1, 1).x);
    ASSERT_GE(1.0f, fkernel2.value(1, 1).x);
    ASSERT_LE(0.5f, fkernel2.value(1, 1).y);
    ASSERT_GE(1.0f, fkernel2.value(1, 1).y);
}

TEST_F(sample_test, multi_jittered_one_sample_per_stratum)
{
    auto fkernel2 = glkernel::kernel2{ 5, 3 };
 
    glkernel::sample::multi_jittered(fkernel2);
    // check if exactly one sample is in the upper left stratum
    unsigned int count = 0;
    for (size_t i = 0; i < fkernel2.size(); ++i)
    {
        auto sample = fkernel2[i];
        if (0.f <= sample.x && sample.x < 1.f / 5.f && 0.f <= sample.y && sample.y < 1.f / 3.f)
        {
            ++count;
        }
    }
    ASSERT_EQ(1, count);
}

TEST_F(sample_test, multi_jittered_one_sample_per_column)
{
    auto fkernel2 = glkernel::dkernel2{ 10, 10 };

    glkernel::sample::multi_jittered(fkernel2);

    // test if first column contains one sample
    unsigned int count = 0;
    for (size_t i = 0; i < fkernel2.size(); ++i)
    {
        auto &sample = fkernel2[i];
        if (0.f <= sample.x && sample.x < 1.f / (10.f * 10.f))
        {
            ++count;
        }
    }
    ASSERT_EQ(1, count);
}

TEST_F(sample_test, multi_jittered_one_sample_per_row)
{
    auto fkernel2 = glkernel::dkernel2{ 10, 10 };

    glkernel::sample::multi_jittered(fkernel2);

    // test if first row contains one sample
    unsigned int count = 0;
    for (size_t i = 0; i < fkernel2.size(); ++i)
    {
        auto &sample = fkernel2[i];
        if (0.f <= sample.y && sample.y < 1.f / (10.f * 10.f))
        {
            ++count;
        }
    }
    ASSERT_EQ(1, count);
}
