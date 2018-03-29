#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glkernel/Kernel.h>
#include <glkernel/sample.h>

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


#if defined SAMPLE_POISSON_SQUARE_1
    glkernel::sample::poisson_square(fkernel1);
#elif defined SAMPLE_POISSON_SQUARE_2
    glkernel::sample::poisson_square(fkernel1, 1.5);
#elif defined SAMPLE_POISSON_SQUARE_3
    glkernel::sample::poisson_square(fkernel1, glm::vec2{ 1.5 });
#elif defined SAMPLE_POISSON_SQUARE_4
    glkernel::sample::poisson_square(fkernel2, 1.5);
#elif defined SAMPLE_POISSON_SQUARE_5
    glkernel::sample::poisson_square(fkernel2, glm::vec2{ 1.5 });
#elif defined SAMPLE_POISSON_SQUARE_6
    glkernel::sample::poisson_square(fkernel2, glm::vec3{ 1.5 });
#elif defined SAMPLE_POISSON_SQUARE_7
    glkernel::sample::poisson_square(fkernel3);
#elif defined SAMPLE_POISSON_SQUARE_8
    glkernel::sample::poisson_square(fkernel3, 1.5);
#elif defined SAMPLE_POISSON_SQUARE_9
    glkernel::sample::poisson_square(fkernel3, glm::vec2{ 1.5 });
#elif defined SAMPLE_STRATIFIED_1
    glkernel::sample::stratified(fkernel4);
#elif defined SAMPLE_HAMMERSLEY_1
    glkernel::sample::hammersley(fkernel1);
#elif defined SAMPLE_HAMMERSLEY_2
    glkernel::sample::hammersley(fkernel3);
#elif defined SAMPLE_HALTON_1
    glkernel::sample::halton(fkernel1, 2, 3);
#elif defined SAMPLE_HALTON_2
    glkernel::sample::halton(fkernel3, 2, 3);
#elif defined SAMPLE_HAMMERSLEY_SPHERE_1
    glkernel::sample::hammersley_sphere(fkernel1);
#elif defined SAMPLE_HAMMERSLEY_SPHERE_2
    glkernel::sample::hammersley_sphere(fkernel2);
#elif defined SAMPLE_HALTON_SPHERE_1
    glkernel::sample::halton_sphere(fkernel1, 2, 3);
#elif defined SAMPLE_HALTON_SPHERE_2
    glkernel::sample::halton_sphere(fkernel2, 2, 3);
#elif defined SAMPLE_BEST_CANDIDATE_1
    glkernel::sample::best_candidate(fkernel1);
#elif defined SAMPLE_BEST_CANDIDATE_2
    glkernel::sample::best_candidate(fkernel4);
#elif defined SAMPLE_NROOKS_1
    glkernel::sample::n_rooks(fkernel1);
#elif defined SAMPLE_NROOKS_2
    glkernel::sample::n_rooks(fkernel3);
#elif defined SAMPLE_MULTI_JITTERED_1
    glkernel::sample::multi_jittered(fkernel1);
#elif defined SAMPLE_MULTI_JITTERED_2
    glkernel::sample::multi_jittered(fkernel3);
#elif defined SAMPLE_GOLDEN_POINT_SET_1
    glkernel::sample::golden_point_set(fkernel1);
#elif defined SAMPLE_GOLDEN_POINT_SET_2
    glkernel::sample::golden_point_set(fkernel3);
#endif

    return 0;
}


