#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glkernel/Kernel.h>
#include <glkernel/scale.h>

#include <iostream>

int main()
{
    auto fkernel1 = glkernel::kernel1{ 1 };
    auto fkernel2 = glkernel::kernel2{ 1 };
    auto fkernel3 = glkernel::kernel3{ 1 };
    auto fkernel4 = glkernel::kernel4{ 1 };

    auto dkernel1 = glkernel::dkernel1{ 1 };
    auto dkernel2 = glkernel::dkernel2{ 1 };
    auto dkernel3 = glkernel::dkernel3{ 1 };


#if defined SCALE_RANGE_1
    glkernel::scale::range(fkernel1, -0.5, 0.5f, 5.f, 10.f);
#elif defined SCALE_RANGE_2
    glkernel::scale::range(fkernel1, -0.5f, 0.5f, 5.f, 10.0);
#elif defined SCALE_RANGE_3
    glkernel::scale::range(fkernel1, glm::vec2{ -0.5 }, 0.5f, 5.f, 10.f);
#elif defined SCALE_RANGE_4
    glkernel::scale::range(fkernel3, -0.5, 0.5f, 5.f, glm::vec3(10.0));
#elif defined SCALE_RANGE_5
    glkernel::scale::range(fkernel3, -0.5, 0.5f, 5.f, 10.f);
#elif defined SCALE_RANGE_6
    glkernel::scale::range(fkernel3, -0.5f, 0.5f, 5.f, 10.0);
#elif defined SCALE_RANGE_7
    glkernel::scale::range(fkernel3, glm::vec2{ -0.5 }, 0.5f, 5.f, 10.f);
#elif defined SCALE_RANGE_8
    glkernel::scale::range(fkernel3, -0.5, 0.5f, 5.f, glm::vec3(10.0));
#endif

    return 0;
}


