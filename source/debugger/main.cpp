
#include <glkernel/Kernel.h>


int main(int /*argc*/, char* /*argv*/[])
{
    auto noise2 = glkernel::Kernel<glm::vec2>(16, 16);

    noise2[6] = glm::vec2(1.f, 2.f);

    noise2.element(9, 2) = glm::vec2(3.f, 4.f);

    // ToDo: glkernel::white_noise(noise2);

    return 0;
}
