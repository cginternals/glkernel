
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