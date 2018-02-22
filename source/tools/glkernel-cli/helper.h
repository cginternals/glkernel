#pragma once

#include <glkernel/Kernel.h>

#include <cppexpose/variant/Variant.h>

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

bool canBeFloat(const cppexpose::Variant & v);
bool canBeVec2(const cppexpose::Variant & v);
bool canBeVec3(const cppexpose::Variant & v);
bool canBeVec4(const cppexpose::Variant & v);

float variantToFloat(const cppexpose::Variant & v);
glm::vec2 variantToVec2(const cppexpose::Variant & v);
glm::vec3 variantToVec3(const cppexpose::Variant & v);
glm::vec4 variantToVec4(const cppexpose::Variant & v);
