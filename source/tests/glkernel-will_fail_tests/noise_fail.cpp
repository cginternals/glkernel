#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glkernel/Kernel.h>
#include <glkernel/noise.h>

#include <iostream>

int main()
{
    auto fkernel1 = glkernel::kernel1{ 1 };
    auto fkernel2 = glkernel::kernel2{ 1 };

    auto dkernel1 = glkernel::dkernel1{ 1 };
    auto dkernel2 = glkernel::dkernel2{ 1 };


#if defined NOISE_NORMAL_1
    glkernel::noise::normal(fkernel1, 0.0f, 1.0);
#elif defined NOISE_NORMAL_2
    glkernel::noise::normal(fkernel1, glm::vec2{ 0.0 }, 1.0f);
#elif defined NOISE_NORMAL_3
    glkernel::noise::normal(fkernel1, 0.0f, glm::vec2{ 0.0 });
#elif defined NOISE_NORMAL_4
    glkernel::noise::normal(fkernel2, 0.0f, 1.0);
#elif defined NOISE_NORMAL_5
    glkernel::noise::normal(fkernel2, glm::vec2{ 0.0 }, 1.0f);
#elif defined NOISE_NORMAL_6
    glkernel::noise::normal(fkernel2, 0.0f, glm::vec2{ 1.0 });
#elif defined NOISE_NORMAL_7
    glkernel::noise::normal(fkernel2, glm::dvec2{ 0.0 }, glm::vec2{ 1.0 });
#elif defined NOISE_NORMAL_8
    glkernel::noise::normal(fkernel2, glm::vec2{ 0.0 }, glm::dvec2{ 1.0 });
#elif defined NOISE_NORMAL_9
    glkernel::noise::normal(fkernel2, glm::vec3{ 0.0 }, glm::vec2{ 1.0 });
#elif defined NOISE_NORMAL_10
    glkernel::noise::normal(fkernel2, glm::vec2{ 0.0 }, glm::vec3{ 1.0 });
#elif defined NOISE_NORMAL_11
    glkernel::noise::normal(fkernel2, glm::dvec3{ 0.0 }, glm::vec2{ 1.0 });
#elif defined NOISE_NORMAL_12
    glkernel::noise::normal(fkernel2, glm::vec2{ 0.0 }, glm::dvec3{ 1.0 });
#elif defined NOISE_NORMAL_13
    glkernel::noise::normal(fkernel2, glm::vec3{ 0.0 }, glm::dvec2{ 1.0 });
#elif defined NOISE_NORMAL_14
    glkernel::noise::normal(fkernel2, glm::vec2{ 0.0 }, glm::dvec3{ 1.0 });
#elif defined NOISE_UNIFORM_1
    glkernel::noise::uniform(fkernel1, 0.0f, 1.0);
#elif defined NOISE_UNIFORM_2
    glkernel::noise::uniform(fkernel1, glm::vec2{ 0.0 }, 1.0f);
#elif defined NOISE_UNIFORM_3
    glkernel::noise::uniform(fkernel1, 0.0f, glm::vec2{ 0.0 });
#elif defined NOISE_UNIFORM_4
    glkernel::noise::uniform(fkernel2, 0.0f, 1.0);
#elif defined NOISE_UNIFORM_5
    glkernel::noise::uniform(fkernel2, glm::vec2{ 0.0 }, 1.0f);
#elif defined NOISE_UNIFORM_6
    glkernel::noise::uniform(fkernel2, 0.0f, glm::vec2{ 1.0 });
#elif defined NOISE_UNIFORM_7
    glkernel::noise::uniform(fkernel2, glm::dvec2{ 0.0 }, glm::vec2{ 1.0 });
#elif defined NOISE_UNIFORM_8
    glkernel::noise::uniform(fkernel2, glm::vec2{ 0.0 }, glm::dvec2{ 1.0 });
#elif defined NOISE_UNIFORM_9
    glkernel::noise::uniform(fkernel2, glm::vec3{ 0.0 }, glm::vec2{ 1.0 });
#elif defined NOISE_UNIFORM_10
    glkernel::noise::uniform(fkernel2, glm::vec2{ 0.0 }, glm::vec3{ 1.0 });
#elif defined NOISE_UNIFORM_11
    glkernel::noise::uniform(fkernel2, glm::dvec3{ 0.0 }, glm::vec2{ 1.0 });
#elif defined NOISE_UNIFORM_12
    glkernel::noise::uniform(fkernel2, glm::vec2{ 0.0 }, glm::dvec3{ 1.0 });
#elif defined NOISE_UNIFORM_13
    glkernel::noise::uniform(fkernel2, glm::vec3{ 0.0 }, glm::dvec2{ 1.0 });
#elif defined NOISE_UNIFORM_14
    glkernel::noise::uniform(fkernel2, glm::vec2{ 0.0 }, glm::dvec3{ 1.0 });
#elif defined NOISE_GRADIENT_1
    glkernel::noise::gradient(dkernel2);
#endif


    return 0;
}
