
#include <gmock/gmock.h>


#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glkernel/Kernel.h>
#include <glkernel/sequence.h>


class sequence_test: public testing::Test
{
public:
};

TEST_F(sequence_test, uniform_compile)
{
    auto fkernel1 = glkernel::kernel1{ 1 };
    auto fkernel2 = glkernel::kernel2{ 1 };
    auto fkernel3 = glkernel::kernel3{ 1 };
    auto fkernel4 = glkernel::kernel4{ 1 };

    glkernel::sequence::uniform(fkernel1, 0.f, 1.f);
    glkernel::sequence::uniform(fkernel2, 0.f, 1.f);
    glkernel::sequence::uniform(fkernel3, 0.f, 1.f);
    glkernel::sequence::uniform(fkernel4, 0.f, 1.f);

    glkernel::sequence::uniform(fkernel2, glm::vec2{ 0.f }, glm::vec2{ 1.f });
    glkernel::sequence::uniform(fkernel3, glm::vec3{ 0.f }, glm::vec3{ 1.f });
    glkernel::sequence::uniform(fkernel4, glm::vec4{ 0.f }, glm::vec4{ 1.f });

    auto dkernel1 = glkernel::dkernel1{ 1 };
    auto dkernel2 = glkernel::dkernel2{ 1 };
    auto dkernel3 = glkernel::dkernel3{ 1 };
    auto dkernel4 = glkernel::dkernel4{ 1 };

    glkernel::sequence::uniform(dkernel1, 0.0, 1.0);
    glkernel::sequence::uniform(dkernel2, 0.0, 1.0);
    glkernel::sequence::uniform(dkernel3, 0.0, 1.0);
    glkernel::sequence::uniform(dkernel4, 0.0, 1.0);

    glkernel::sequence::uniform(dkernel2, glm::dvec2{ 0.0 }, glm::dvec2{ 1.0 });
    glkernel::sequence::uniform(dkernel3, glm::dvec3{ 0.0 }, glm::dvec3{ 1.0 });
    glkernel::sequence::uniform(dkernel4, glm::dvec4{ 0.0 }, glm::dvec4{ 1.0 });
}

TEST_F(sequence_test, uniform_distribution)
{
    auto fkernel1 = glkernel::kernel1{ 4 };

    glkernel::sequence::uniform(fkernel1, 0.f, 1.f);

    EXPECT_FLOAT_EQ(0.f / 3.f, fkernel1[0]);
    EXPECT_FLOAT_EQ(1.f / 3.f, fkernel1[1]);
    EXPECT_FLOAT_EQ(2.f / 3.f, fkernel1[2]);
    EXPECT_FLOAT_EQ(3.f / 3.f, fkernel1[3]);

    auto fkernel4 = glkernel::kernel4{ 3 };

    glkernel::sequence::uniform(fkernel4, glm::vec4{ 0.f, 1.f, 2.f, 3.f }, glm::vec4{ 1.f, 2.f, 3.f, 4.f });

    EXPECT_FLOAT_EQ(0.f / 2.f, fkernel4[0][0]);
    EXPECT_FLOAT_EQ(1.f / 2.f, fkernel4[1][0]);
    EXPECT_FLOAT_EQ(2.f / 2.f, fkernel4[2][0]);
    
    EXPECT_FLOAT_EQ(2.f / 2.f, fkernel4[0][1]);
    EXPECT_FLOAT_EQ(3.f / 2.f, fkernel4[1][1]);
    EXPECT_FLOAT_EQ(4.f / 2.f, fkernel4[2][1]);

    EXPECT_FLOAT_EQ(4.f / 2.f, fkernel4[0][2]);
    EXPECT_FLOAT_EQ(5.f / 2.f, fkernel4[1][2]);
    EXPECT_FLOAT_EQ(6.f / 2.f, fkernel4[2][2]);

    EXPECT_FLOAT_EQ(6.f / 2.f, fkernel4[0][3]);
    EXPECT_FLOAT_EQ(7.f / 2.f, fkernel4[1][3]);
    EXPECT_FLOAT_EQ(8.f / 2.f, fkernel4[2][3]);
}
