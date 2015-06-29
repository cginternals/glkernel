#pragma once

#include <type_traits>

#include <glm/gtc/type_precision.hpp>

#include <glkernel/kernel.h>


namespace glkernel
{

class noise
{
    noise() = delete;

public:

    // NORMAL: generates gaussian distributed random values for given mean and standard deviation

    template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
    static void normal(tkernel<T> & kernel, T mean, T stddev);

    template <typename T, glm::precision P, template<typename, glm::precision> class V>
    static void normal(tkernel<V<T, P>> & kernel, T mean, T stddev);

    template <typename T, glm::precision P, template<typename, glm::precision> class V>
    static void normal(tkernel<V<T, P>> & kernel, const V<T, P> & mean, const V<T, P> & stddev);

    //template <typename T, glm::precision P>
    //static void normal(tkernel<glm::tvec2<T, P>> & kernel, T mean, T stddev);
    //template <typename T, glm::precision P>
    //static void normal(tkernel<glm::tvec3<T, P>> & kernel, T mean, T stddev);
    //template <typename T, glm::precision P>
    //static void normal(tkernel<glm::tvec4<T, P>> & kernel, T mean, T stddev);

    // ToDo: somehow unify the following forward declarations with:
    //template <typename T, glm::precision P, template<typename, glm::precision> class V>
    //static void normal(tkernel<V<T, P>> & kernel, const V<T, P> & mean, const V<T, P> & stddev);

    /*template <typename T, glm::precision P>
    static void normal(tkernel<glm::tvec2<T, P>> & kernel, const glm::tvec2<T, P> & mean, const glm::tvec2<T, P> & stddev);
    template <typename T, glm::precision P>
    static void normal(tkernel<glm::tvec3<T, P>> & kernel, const glm::tvec3<T, P> & mean, const glm::tvec3<T, P> & stddev);
    template <typename T, glm::precision P>
    static void normal(tkernel<glm::tvec4<T, P>> & kernel, const glm::tvec4<T, P> & mean, const glm::tvec4<T, P> & stddev);
*/

    // UNIFORM: generates uniform distributed random values within a given range

    template<typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 0>
    static void uniform(tkernel<T> & kernel, T range_min, T range_max);

    // ToDo: somehow unify the following forward declarations with:
    //template <typename T, glm::precision P, template<typename, glm::precision> class V>
    //static void uniform(tkernel<V<T, P>> & kernel, const T range_min, const T range_max);

    template <typename T, glm::precision P>
    static void uniform(tkernel<glm::tvec2<T, P>> & kernel, T range_min, T range_max);
    template <typename T, glm::precision P>
    static void uniform(tkernel<glm::tvec3<T, P>> & kernel, T range_min, T range_max);
    template <typename T, glm::precision P>
    static void uniform(tkernel<glm::tvec4<T, P>> & kernel, T range_min, T range_max);

    // ToDo: somehow unify the following forward declarations with:
    //template <typename T, glm::precision P, template<typename, glm::precision> class V>
    //static void uniform(tkernel<V<T, P>> & kernel, const V<T, P> & range_min, const V<T, P> & range_max);

    template <typename T, glm::precision P>
    static void uniform(tkernel<glm::tvec2<T, P>> & kernel, const glm::tvec2<T, P> & range_min, const glm::tvec2<T, P> & range_max);
    template <typename T, glm::precision P>
    static void uniform(tkernel<glm::tvec3<T, P>> & kernel, const glm::tvec3<T, P> & range_min, const glm::tvec3<T, P> & range_max);
    template <typename T, glm::precision P>
    static void uniform(tkernel<glm::tvec4<T, P>> & kernel, const glm::tvec4<T, P> & range_min, const glm::tvec4<T, P> & range_max);

private:

    template <typename T>
    static void normal_base(T * kernel, size_t size, T mean, T stddev, size_t step, size_t offset);
    template <typename T, int C>
    static void normal_base(T * kernel, size_t size, T mean, T stddev);
    template <typename T, int C>
    static void normal_base(T * kernel, size_t size, const T * mean, const T * stddev);

    template <typename T>
    static void uniform_base(T * kernel, size_t size, T range_min, T range_max, size_t step, size_t offset);
    template <typename T, int C>
    static void uniform_base(T * kernel, size_t size, T range_min, T range_max);
    template <typename T, int C>
    static void uniform_base(T * kernel, size_t size, const T * range_min, const T * range_max);
 };

} // namespace glkernel

#include <glkernel/noise.hpp>
