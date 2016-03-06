
#include <gmock/gmock.h>


#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glkernel/Kernel.h>
#include <glkernel/shuffle.h>


class shuffle_test: public testing::Test
{
public:
};

TEST_F(shuffle_test, bucket_permutate_compile)
{
    auto fkernel1 = glkernel::kernel1{ 8, 8, 8 };
    glkernel::shuffle::bucket_permutate(fkernel1, 2, 2, 2, true);
}

TEST_F(shuffle_test, bayer_compile)
{
    {   auto fkernel1 = glkernel::kernel1{ 2, 2 };
        glkernel::shuffle::bayer(fkernel1); }

    {   auto fkernel1 = glkernel::kernel1{ 3, 3 };
        glkernel::shuffle::bayer(fkernel1); }

    {   auto fkernel1 = glkernel::kernel1{ 4, 4 };
        glkernel::shuffle::bayer(fkernel1); }

    {   auto fkernel1 = glkernel::kernel1{ 8, 8 };
        glkernel::shuffle::bayer(fkernel1); }
}

TEST_F(shuffle_test, random_compile)
{
    auto fkernel1 = glkernel::kernel1{ 4, 4 };
    glkernel::shuffle::random(fkernel1);

    auto fkernel2 = glkernel::kernel2{ 4, 4 };
    glkernel::shuffle::random(fkernel2);

    auto fkernel3 = glkernel::kernel3{ 4, 4 };
    glkernel::shuffle::random(fkernel3);

    auto fkernel4 = glkernel::kernel4{ 4, 4 };
    glkernel::shuffle::random(fkernel4);
}
