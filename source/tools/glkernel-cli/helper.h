#pragma once

#include <glkernel/Kernel.h>

/*
 * Assert a condition and throw otherwise, outputting the user supplied message.
 * Throws for both release and debug builds.
 */
void throwIfNot(bool condition, const std::string& msg);

/*
 * find min and max element in glkernel
 */
// TODO also support double
std::pair<float, float> findMinMaxElements(const glkernel::tkernel<float> & kernel);
std::pair<float, float> findMinMaxElements(const glkernel::tkernel<glm::vec2> & kernel);
std::pair<float, float> findMinMaxElements(const glkernel::tkernel<glm::vec3> & kernel);
std::pair<float, float> findMinMaxElements(const glkernel::tkernel<glm::vec4> & kernel);
