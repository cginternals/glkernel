#include "helper.h"

#include <algorithm>
#include <vector>

#include <glkernel/Kernel.h>

void throwIfNot(bool condition, const std::string& msg)
{
    if (!condition)
    {
        throw std::logic_error(msg);
    }
}

std::pair<float, float> findMinMaxElements(const glkernel::tkernel<float> & kernel)
{
  const auto minmax = std::minmax_element(kernel.cbegin(), kernel.cend());
  return std::make_pair(*minmax.first, *minmax.second);
}

std::pair<float, float> findMinMaxElements(const glkernel::tkernel<glm::vec2> & kernel)
{
  float min = std::numeric_limits<float>::max();
  float max = std::numeric_limits<float>::min();
  const auto end = kernel.cend();
  for (auto it = kernel.cbegin(); it != end; ++it)
  {
    const auto x = it->x;
    const auto y = it->y;

    min = x < min ? x : min;
    min = y < min ? y : min;

    max = x > max ? x : max;
    max = y > max ? y : max;
  }

  return std::make_pair(min, max);
}

std::pair<float, float> findMinMaxElements(const glkernel::tkernel<glm::vec3> & kernel)
{
  float min = std::numeric_limits<float>::max();
  float max = std::numeric_limits<float>::min();
  const auto end = kernel.cend();
  for (auto it = kernel.cbegin(); it != end; ++it)
  {
    const auto x = it->x;
    const auto y = it->y;
    const auto z = it->z;

    min = x < min ? x : min;
    min = y < min ? y : min;
    min = z < min ? z : min;

    max = x > max ? x : max;
    max = y > max ? y : max;
    max = z > max ? z : max;
  }

  return std::make_pair(min, max);
}

std::pair<float, float> findMinMaxElements(const glkernel::tkernel<glm::vec4> & kernel)
{
  float min = std::numeric_limits<float>::max();
  float max = std::numeric_limits<float>::min();
  const auto end = kernel.cend();
  for (auto it = kernel.cbegin(); it != end; ++it)
  {
    const auto x = it->x;
    const auto y = it->y;
    const auto z = it->z;
    const auto w = it->w;

    min = x < min ? x : min;
    min = y < min ? y : min;
    min = z < min ? z : min;
    min = w < min ? z : min;

    max = x > max ? x : max;
    max = y > max ? y : max;
    max = z > max ? z : max;
    max = w > max ? z : max;
  }

  return std::make_pair(min, max);
}
