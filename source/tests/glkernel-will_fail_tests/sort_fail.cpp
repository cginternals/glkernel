#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glkernel/Kernel.h>
#include <glkernel/sort.h>

#include <iostream>

int main()
{
    auto fkernel1 = glkernel::kernel1{ 1 };
    auto fkernel2 = glkernel::kernel2{ 1 };

    auto dkernel1 = glkernel::dkernel1{ 1 };
    auto dkernel2 = glkernel::dkernel2{ 1 };


#if defined SORT_DISTANCE_1
    glkernel::sort::distance(fkernel1, 0.5);
#elif defined SORT_DISTANCE_2
    glkernel::sort::distance(fkernel1, glm::vec3{ 0.5 });
#elif defined SORT_DISTANCE_3
    glkernel::sort::distance(fkernel2, 0.5f);
#elif defined SORT_DISTANCE_4
    glkernel::sort::distance(fkernel2, 0.5);
#elif defined SORT_DISTANCE_5
    glkernel::sort::distance(fkernel2, glm::dvec2{ 0.5 });
#elif defined SORT_DISTANCE_6
    glkernel::sort::distance(fkernel2, glm::vec3{ 0.5 });
#elif defined SORT_DISTANCE_7
    glkernel::sort::distance(fkernel2, glm::dvec3{ 0.5 });
#endif


    return 0;
}
