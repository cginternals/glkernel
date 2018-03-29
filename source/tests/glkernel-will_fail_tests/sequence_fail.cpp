#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glkernel/Kernel.h>
#include <glkernel/sequence.h>

#include <iostream>

int main()
{
    auto fkernel1 = glkernel::kernel1{ 1 };
    auto fkernel2 = glkernel::kernel2{ 1 };

    auto dkernel1 = glkernel::dkernel1{ 1 };
    auto dkernel2 = glkernel::dkernel2{ 1 };


#if defined SEQUENCE_UNIFORM_1
    glkernel::sequence::uniform(fkernel1, 0.0f, 1.0);
#elif defined SEQUENCE_UNIFORM_2
    glkernel::sequence::uniform(fkernel1, glm::vec2{ 0.0 }, 1.0f);
#elif defined SEQUENCE_UNIFORM_3
    glkernel::sequence::uniform(fkernel1, 0.0f, glm::vec2{ 0.0 });
#elif defined SEQUENCE_UNIFORM_4
    glkernel::sequence::uniform(fkernel2, 0.0f, 1.0);
#elif defined SEQUENCE_UNIFORM_5
    glkernel::sequence::uniform(fkernel2, glm::vec2{ 0.0 }, 1.0f);
#elif defined SEQUENCE_UNIFORM_6
    glkernel::sequence::uniform(fkernel2, 0.0f, glm::vec2{ 1.0 });
#elif defined SEQUENCE_UNIFORM_7
    glkernel::sequence::uniform(fkernel2, glm::dvec2{ 0.0 }, glm::vec2{ 1.0 });
#elif defined SEQUENCE_UNIFORM_8
    glkernel::sequence::uniform(fkernel2, glm::vec2{ 0.0 }, glm::dvec2{ 1.0 });
#elif defined SEQUENCE_UNIFORM_9
    glkernel::sequence::uniform(fkernel2, glm::vec3{ 0.0 }, glm::vec2{ 1.0 });
#elif defined SEQUENCE_UNIFORM_10
    glkernel::sequence::uniform(fkernel2, glm::vec2{ 0.0 }, glm::vec3{ 1.0 });
#elif defined SEQUENCE_UNIFORM_11
    glkernel::sequence::uniform(fkernel2, glm::dvec3{ 0.0 }, glm::vec2{ 1.0 });
#elif defined SEQUENCE_UNIFORM_12
    glkernel::sequence::uniform(fkernel2, glm::vec2{ 0.0 }, glm::dvec3{ 1.0 });
#elif defined SEQUENCE_UNIFORM_13
    glkernel::sequence::uniform(fkernel2, glm::vec3{ 0.0 }, glm::dvec2{ 1.0 });
#elif defined SEQUENCE_UNIFORM_14
    glkernel::sequence::uniform(fkernel2, glm::vec2{ 0.0 }, glm::dvec3{ 1.0 });
#endif


    return 0;
}
