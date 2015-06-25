#pragma once

#include <glkernel/Kernel.h>

#include <glm/vec2.hpp>

#include <glkernel/Kernel.h>

#include <glkernel/uniform_noise.h>
#include <glkernel/normal_noise.h>
#include <glkernel/square_points.hpp>


namespace glkernel
{

void test()
{
    { auto noise = glkernel::Kernel<float>();      }
    { auto noise = glkernel::Kernel<double>();     }

    { auto noise = glkernel::Kernel<glm::vec2>();  }
    { auto noise = glkernel::Kernel<glm::dvec2>(); }

    { auto noise = glkernel::Kernel<glm::vec3>();  }
    { auto noise = glkernel::Kernel<glm::dvec3>(); }

    { auto noise = glkernel::Kernel<glm::vec4>();  }
    { auto noise = glkernel::Kernel<glm::dvec4>(); }
}

} // namespace glkernel
