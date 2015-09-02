
#include <gmock/gmock.h>


#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glkernel/Kernel.h>
#include <glkernel/noise.h>


class noise_test: public testing::Test
 {
 public:
 };

TEST_F(noise_test, normal_compile)
{
    auto fkernel1 = glkernel::kernel1{ 1 };
    auto fkernel2 = glkernel::kernel2{ 1 };
    auto fkernel3 = glkernel::kernel3{ 1 };
    auto fkernel4 = glkernel::kernel4{ 1 };

    glkernel::noise::normal(fkernel1, 0.f, 1.f);
    glkernel::noise::normal(fkernel2, 0.f, 1.f);
    glkernel::noise::normal(fkernel3, 0.f, 1.f);
    glkernel::noise::normal(fkernel4, 0.f, 1.f);

    glkernel::noise::normal(fkernel2, glm::vec2{ 0.f }, glm::vec2{ 1.f });
    glkernel::noise::normal(fkernel3, glm::vec3{ 0.f }, glm::vec3{ 1.f });
    glkernel::noise::normal(fkernel4, glm::vec4{ 0.f }, glm::vec4{ 1.f });

    auto dkernel1 = glkernel::dkernel1{ 1 };
    auto dkernel2 = glkernel::dkernel2{ 1 };
    auto dkernel3 = glkernel::dkernel3{ 1 };
    auto dkernel4 = glkernel::dkernel4{ 1 };

    glkernel::noise::normal(dkernel1, 0.0, 1.0);
    glkernel::noise::normal(dkernel2, 0.0, 1.0);
    glkernel::noise::normal(dkernel3, 0.0, 1.0);
    glkernel::noise::normal(dkernel4, 0.0, 1.0);

    glkernel::noise::normal(dkernel2, glm::dvec2{ 0.0 }, glm::dvec2{ 1.0 });
    glkernel::noise::normal(dkernel3, glm::dvec3{ 0.0 }, glm::dvec3{ 1.0 });
    glkernel::noise::normal(dkernel4, glm::dvec4{ 0.0 }, glm::dvec4{ 1.0 });
}

TEST_F(noise_test, uniform_compile)
{
    auto fkernel1 = glkernel::kernel1{ 1 };
    auto fkernel2 = glkernel::kernel2{ 1 };
    auto fkernel3 = glkernel::kernel3{ 1 };
    auto fkernel4 = glkernel::kernel4{ 1 };

    glkernel::noise::uniform(fkernel1, 0.f, 1.f);
    glkernel::noise::uniform(fkernel2, 0.f, 1.f);
    glkernel::noise::uniform(fkernel3, 0.f, 1.f);
    glkernel::noise::uniform(fkernel4, 0.f, 1.f);

    glkernel::noise::uniform(fkernel2, glm::vec2{ 0.f }, glm::vec2{ 1.f });
    glkernel::noise::uniform(fkernel3, glm::vec3{ 0.f }, glm::vec3{ 1.f });
    glkernel::noise::uniform(fkernel4, glm::vec4{ 0.f }, glm::vec4{ 1.f });

    auto dkernel1 = glkernel::dkernel1{ 1 };
    auto dkernel2 = glkernel::dkernel2{ 1 };
    auto dkernel3 = glkernel::dkernel3{ 1 };
    auto dkernel4 = glkernel::dkernel4{ 1 };

    glkernel::noise::uniform(dkernel1, 0.0, 1.0);
    glkernel::noise::uniform(dkernel2, 0.0, 1.0);
    glkernel::noise::uniform(dkernel3, 0.0, 1.0);
    glkernel::noise::uniform(dkernel4, 0.0, 1.0);

    glkernel::noise::uniform(dkernel2, glm::dvec2{ 0.0 }, glm::dvec2{ 1.0 });
    glkernel::noise::uniform(dkernel3, glm::dvec3{ 0.0 }, glm::dvec3{ 1.0 });
    glkernel::noise::uniform(dkernel4, glm::dvec4{ 0.0 }, glm::dvec4{ 1.0 });
}

TEST_F(noise_test, perlin_compile)
{
    auto fkernel1 = glkernel::kernel1{ 1 };
    auto dkernel1 = glkernel::dkernel1{ 1 };

    glkernel::noise::perlin(fkernel1, 1.0f);
    glkernel::noise::perlin(dkernel1, 1.0);
}
