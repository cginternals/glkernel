
#include <gmock/gmock.h>


#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glkernel/Kernel.h>


class tkernel_test: public testing::Test
 {
 public:
 };

TEST_F(tkernel_test, tkernel_indexed_value_access)
{
    auto fkernel = glkernel::kernel1(2, 4, 8);

    EXPECT_EQ(64u, fkernel.size());
    EXPECT_EQ( 2u, fkernel.width());
    EXPECT_EQ( 4u, fkernel.height());
    EXPECT_EQ( 8u, fkernel.depth());

    // check if a value set in kernel via spatial reference 
    // equals the value at the expected index ...

    const auto findex = fkernel.index(1, 2, 3);
    EXPECT_EQ(static_cast<unsigned int>(2 * 4 * 3 + 2 * 2 + 1), findex);

    fkernel[findex] = 1.f;
    EXPECT_EQ(1.f, fkernel.value(1, 2, 3));
}

TEST_F(tkernel_test, tkernel_data_access)
{
    auto fkernel = glkernel::kernel1(8, 2, 4);

    EXPECT_EQ(64u, fkernel.size());
    EXPECT_EQ( 8u, fkernel.width());
    EXPECT_EQ( 2u, fkernel.height());
    EXPECT_EQ( 4u, fkernel.depth());

    // check if a value set in kernel via spatial reference 
    // equals the value at the expected index ...

    const auto findex = fkernel.index(2, 1, 3);
    EXPECT_EQ(static_cast<unsigned int>(8 * 2 * 3 + 8 * 1 + 2), findex);

    fkernel[findex] = 1.f;
    EXPECT_EQ(1.f, fkernel.data()[findex]);
}

TEST_F(tkernel_test, tkernel_reset)
{
    auto fkernel = glkernel::kernel1(1024);

    EXPECT_EQ(1024u, fkernel.size());
    EXPECT_EQ(1024u, fkernel.width());
    EXPECT_EQ(   1u, fkernel.height());
    EXPECT_EQ(   1u, fkernel.depth());

    {   auto accum = 0.f; // checksum
        for (size_t i = 0; i < fkernel.size(); accum += fkernel[i++]);
        EXPECT_EQ(0.f, accum);   }

    for (size_t i = 0; i < fkernel.size(); ++i)
        fkernel[i] = 1.0f;

    {   auto accum = 0.f; // checksum
        for (size_t i = 0; i < fkernel.size(); accum += fkernel[i++]);
        EXPECT_EQ(static_cast<float>(fkernel.size()), accum);   }

    fkernel.reset();

    {   auto accum = 0.f; // checksum
        for (size_t i = 0; i < fkernel.size(); accum += fkernel[i++]);
        EXPECT_EQ(0.f, accum);   }
}

TEST_F(tkernel_test, tkernel_trim)
{
    auto fkernel = glkernel::kernel3(4, 2, 8);

    for (glm::uint16 r = 0; r < fkernel.depth(); ++r)
        for (glm::uint16 t = 0; t < fkernel.height(); ++t)
            for (glm::uint16 s = 0; s < fkernel.width(); ++s)
                fkernel.value(s, t, r) = glm::vec3(s, t, r);

    const auto trimmed = fkernel.trimed(2, 2, 2);

    for (glm::uint16 r = 0; r < trimmed.depth(); ++r)
        for (glm::uint16 t = 0; t < trimmed.height(); ++t)
            for (glm::uint16 s = 0; s < trimmed.width(); ++s)
                EXPECT_EQ(glm::vec3(s, t, r), fkernel.value(s, t, r));
}

TEST_F(tkernel_test, tkernel1_defaults)
{
    const auto fkernel = glkernel::kernel1{};

    EXPECT_EQ(1u, fkernel.size());
    EXPECT_EQ(1u, fkernel.width());
    EXPECT_EQ(1u, fkernel.height());
    EXPECT_EQ(1u, fkernel.depth());
     
    EXPECT_EQ(0.f, fkernel.value(0, 0, 0));
 
    const auto dkernel = glkernel::dkernel1{};

    EXPECT_EQ(1u, dkernel.size());
    EXPECT_EQ(1u, dkernel.width());
    EXPECT_EQ(1u, dkernel.height());
    EXPECT_EQ(1u, dkernel.depth());

    EXPECT_EQ(0.0, dkernel.value(0, 0, 0));
}

TEST_F(tkernel_test, tkernel2_defaults)
{
    const auto fkernel = glkernel::kernel2{};

    EXPECT_EQ(1u, fkernel.size());
    EXPECT_EQ(1u, fkernel.width());
    EXPECT_EQ(1u, fkernel.height());
    EXPECT_EQ(1u, fkernel.depth());

    EXPECT_EQ(glm::vec2(0.f, 0.f), fkernel.value(0, 0, 0));

    const auto dkernel = glkernel::dkernel2{};

    EXPECT_EQ(1u, dkernel.size());
    EXPECT_EQ(1u, dkernel.width());
    EXPECT_EQ(1u, dkernel.height());
    EXPECT_EQ(1u, dkernel.depth());

    EXPECT_EQ(glm::dvec2(0.0, 0.0), dkernel.value(0, 0, 0));
}

TEST_F(tkernel_test, tkernel3_defaults)
{
    const auto fkernel = glkernel::kernel3{};

    EXPECT_EQ(1u, fkernel.size());
    EXPECT_EQ(1u, fkernel.width());
    EXPECT_EQ(1u, fkernel.height());
    EXPECT_EQ(1u, fkernel.depth());

    EXPECT_EQ(glm::vec3(0.f, 0.f, 0.f), fkernel.value(0, 0, 0));

    const auto dkernel = glkernel::dkernel3{};

    EXPECT_EQ(1u, dkernel.size());
    EXPECT_EQ(1u, dkernel.width());
    EXPECT_EQ(1u, dkernel.height());
    EXPECT_EQ(1u, dkernel.depth());

    EXPECT_EQ(glm::dvec3(0.0, 0.0, 0.0), dkernel.value(0, 0, 0));
}

TEST_F(tkernel_test, tkernel4_defaults)
{
    const auto fkernel = glkernel::kernel4{};

    EXPECT_EQ(1u, fkernel.size());
    EXPECT_EQ(1u, fkernel.width());
    EXPECT_EQ(1u, fkernel.height());
    EXPECT_EQ(1u, fkernel.depth());

    EXPECT_EQ(glm::vec4(0.f, 0.f, 0.f, 0.f), fkernel.value(0, 0, 0));

    const auto dkernel = glkernel::dkernel4{};

    EXPECT_EQ(1u, dkernel.size());
    EXPECT_EQ(1u, dkernel.width());
    EXPECT_EQ(1u, dkernel.height());
    EXPECT_EQ(1u, dkernel.depth());

    EXPECT_EQ(glm::dvec4(0.0, 0.0, 0.0, 0.0), dkernel.value(0, 0, 0));
}

TEST_F(tkernel_test, tkernel_lengths)
{
    const auto fkernel1 = glkernel::kernel1{};
    EXPECT_EQ(1, fkernel1.length());

    const auto fkernel2 = glkernel::kernel2{};
    EXPECT_EQ(2, fkernel2.length());

    const auto fkernel3 = glkernel::kernel3{};
    EXPECT_EQ(3, fkernel3.length());

    const auto fkernel4 = glkernel::kernel4{};
    EXPECT_EQ(4, fkernel4.length());

    const auto dkernel1 = glkernel::dkernel1{};
    EXPECT_EQ(1, dkernel1.length());

    const auto dkernel2 = glkernel::dkernel2{};
    EXPECT_EQ(2, dkernel2.length());

    const auto dkernel3 = glkernel::dkernel3{};
    EXPECT_EQ(3, dkernel3.length());

    const auto dkernel4 = glkernel::dkernel4{};
    EXPECT_EQ(4, dkernel4.length());
}
