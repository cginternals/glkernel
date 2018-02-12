#include <algorithm>
#include <vector>

/*
 * write cell value to png
 */
template <typename T>
void writeData(T cellValue, png_bytep outputRow, int x);

/*
 * bit depth 16: we need 2 bytes per cell value
 */
template <>
void writeData(float cellValue, png_bytep outputRow, int x)
{
  png_save_uint_16(outputRow + 2 * x, static_cast<uint16_t>(cellValue));
}

template <>
void writeData(glm::vec2 cellValue, png_bytep outputRow, int x)
{
  png_save_uint_16(outputRow + 4 * x, static_cast<uint16_t>(cellValue.x));
  png_save_uint_16(outputRow + 4 * x + 2, static_cast<uint16_t>(cellValue.y));
}

template <>
void writeData(glm::vec3 cellValue, png_bytep outputRow, int x)
{
  png_save_uint_16(outputRow + 6 * x, static_cast<uint16_t>(cellValue.x));
  png_save_uint_16(outputRow + 6 * x + 2, static_cast<uint16_t>(cellValue.y));
  png_save_uint_16(outputRow + 6 * x + 4, static_cast<uint16_t>(cellValue.z));
}

template <>
void writeData(glm::vec4 cellValue, png_bytep outputRow, int x)
{
  png_save_uint_16(outputRow + 8 * x, static_cast<uint16_t>(cellValue.x));
  png_save_uint_16(outputRow + 8 * x + 2, static_cast<uint16_t>(cellValue.y));
  png_save_uint_16(outputRow + 8 * x + 4, static_cast<uint16_t>(cellValue.z));
  png_save_uint_16(outputRow + 8 * x + 6, static_cast<uint16_t>(cellValue.w));
}

/*
 * find min and max element in glkernel
 */
// TODO also support double
template <typename T>
std::pair<float, float> findMinMaxElements(const glkernel::tkernel<T> & kernel);

template <>
std::pair<float, float> findMinMaxElements(const glkernel::tkernel<float> & kernel)
{
  const auto minmax = std::minmax_element(kernel.cbegin(), kernel.cend());
  return std::make_pair(*minmax.first, *minmax.second);
}

template <>
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

template <>
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

template <>
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