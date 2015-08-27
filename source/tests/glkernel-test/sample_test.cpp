
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

TEST_F(sample_test, n_rooks_compile)
{
    auto fkernel2 = glkernel::kernel2{ 1 };

    glkernel::sample::n_rooks(fkernel2);

    auto dkernel2 = glkernel::dkernel2{ 1 };

    glkernel::sample::n_rooks(dkernel2);
}

TEST_F(sample_test, n_one_sample_per_column)
{
    auto fkernel2 = glkernel::kernel2{ 20 };

    glkernel::sample::n_rooks(fkernel2);

    // test if first column contains one sample
    unsigned int count = 0;
    for (size_t i = 0; i < fkernel2.size(); ++i)
    {
        auto &sample = fkernel2[i];
        if (0.f <= sample.x && sample.x < 1.f / 20.f)
        {
            ++count;
        }
    }
    ASSERT_EQ(1, count);
}

TEST_F(sample_test, n_one_sample_per_row)
{
    auto fkernel2 = glkernel::kernel2{ 20 };

    glkernel::sample::n_rooks(fkernel2);

    // test if first row contains one sample
    unsigned int count = 0;
    for (size_t i = 0; i < fkernel2.size(); ++i)
    {
        auto &sample = fkernel2[i];
        if (0.f <= sample.y && sample.y < 1.f / 20.f)
        {
            ++count;
        }
    }
    ASSERT_EQ(1, count);
}
