#pragma once

#include <glkernel/noise.h>

#include <glkernel/glm_compatability.h>


namespace glkernel
{

namespace noise
{


template <typename T>
class uniform_operator
{
public:
    uniform_operator(size_t size, glm::length_t
        , T range_min, T range_max);

    template <typename F, glm::precision P, template<typename, glm::precision> class V>
    uniform_operator(size_t size, glm::length_t coefficient
        , const V<F, P> & range_min, const V<F, P> range_max);

    T operator()(const size_t index);

protected:
    std::mt19937_64 m_generator;
    std::uniform_real_distribution<T> m_distribute;
};


template<typename T>
uniform_operator<T>::uniform_operator(const size_t, const glm::length_t
    , const T range_min, const T range_max)
: m_generator{ std::random_device{ }() }
, m_distribute{ range_min, range_max }
{
}

template <typename T>
template <typename F, glm::precision P, template<typename, glm::precision> class V>
uniform_operator<T>::uniform_operator(const size_t size, const glm::length_t coefficient
    , const V<F, P> & range_min, const V<F, P> range_max)
: uniform_operator{ size, coefficient, range_min[coefficient], range_max[coefficient] }
{
}

template<typename T>
T uniform_operator<T>::operator()(const size_t)
{
    return m_distribute(m_generator);
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type *>
void uniform(tkernel<T> & kernel, const T range_min, const T range_max)
{
    kernel.for_each<uniform_operator<T>>(range_min, range_max);
}

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void uniform(tkernel<V<T, P>> & kernel, const T range_min, const T range_max)
{
    kernel.for_each<uniform_operator<T>>(range_min, range_max);
}

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void uniform(tkernel<V<T, P>> & kernel, const V<T, P> & range_min, const V<T, P> & range_max)
{
    kernel.for_each<uniform_operator<T>>(range_min, range_max);
}


template <typename T>
class normal_operator
{
public:
    normal_operator(size_t size, glm::length_t
        , T mean, T stddev);

    template <typename F, glm::precision P, template<typename, glm::precision> class V>
    normal_operator(size_t size, glm::length_t coefficient
        , const V<F, P> & mean, const V<F, P> stddev);

    T operator()(const size_t index);

protected:
    std::mt19937_64 m_generator;
    std::uniform_real_distribution<T> m_distribute;
};


template <typename T>
normal_operator<T>::normal_operator(const size_t, const glm::length_t
    , const T mean, const T stddev)
: m_generator{ std::random_device{}() }
, m_distribute{ mean, stddev }
{
}

template <typename T>
template <typename F, glm::precision P, template<typename, glm::precision> class V>
normal_operator<T>::normal_operator(const size_t size, const glm::length_t coefficient
    , const V<F, P> & mean, const V<F, P> stddev)
: normal_operator{ size, coefficient, mean[coefficient], stddev[coefficient] }
{
}

template<typename T>
T normal_operator<T>::operator()(const size_t)
{
    return m_distribute(m_generator);
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type *>
void normal(tkernel<T> & kernel, const T mean, const T stddev)
{
    kernel.for_each<normal_operator<T>>(mean, stddev);
}

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void normal(tkernel<V<T, P>> & kernel, const T mean, const T stddev)
{
    kernel.for_each<normal_operator<T>>(mean, stddev);
}

template <typename T, glm::precision P, template<typename, glm::precision> class V>
void normal(tkernel<V<T, P>> & kernel, const V<T, P> & mean, const V<T, P> & stddev)
{
    kernel.for_each<normal_operator<T>>(mean, stddev);
}

// From // JAVA REFERENCE IMPLEMENTATION OF IMPROVED NOISE - COPYRIGHT 2002 KEN PERLIN. (http://mrl.nyu.edu/~perlin/noise/)
// and (Improving Noise - Perlin - 2002) - http://mrl.nyu.edu/~perlin/paper445.pdf

const unsigned char perm[] =
{
    151, 160, 137, 91, 90, 15,
    131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23,
    190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 32, 57, 177, 33,
    88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166,
    77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46, 245, 40, 244,
    102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132, 187, 208, 89, 18, 169, 200, 196,
    135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123,
    5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182, 189, 28, 42,
    223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221, 153, 101, 155, 167, 43, 172, 9,
    129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228,
    251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107,
    49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45, 127, 4, 150, 254,
    138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180
};

const float grad[16][3] =
{
    { 1.f, 1.f, 0.f }, { -1.f, 1.f, 0.f }, { 1.f, -1.f, 0.f }, { -1.f, -1.f, 0.f }
    , { 1.f, 0.f, 1.f }, { -1.f, 0.f, 1.f }, { 1.f, 0.f, -1.f }, { -1.f, 0.f, -1.f }
    , { 0.f, 1.f, 1.f }, { 0.f, -1.f, 1.f }, { 0.f, 1.f, -1.f }, { 0.f, -1.f, -1.f }
    , { 1.f, 1.f, 0.f }, { -1.f, 1.f, 0.f }, { 0.f, -1.f, 0.f }, { 0.f, -1.f, -1.f }
};

const unsigned int MAXPERMINDEX(0xff);
const unsigned int PERMSIZE(0xff);

const unsigned int hash(
    const unsigned int x
    , const unsigned int y
    , const unsigned int r)
{
    assert(1 << r <= PERMSIZE);
    return perm[(perm[x & ((1 << r) - 1)] + y) & ((1 << r) - 1)];
}

const glm::vec2 grad2(
    const unsigned int x
    , const unsigned int y
    , const unsigned int r)
{
    const auto p = static_cast<unsigned char>(hash(x, y, r));
    return glm::vec2(grad[p & 0xf][0], grad[p & 0xf][1]);
}

double fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

const float noise2(
    const float s
    , const float t
    , const unsigned int r)
{
    float s_ = s * (1 << r);
    float t_ = t * (1 << r);

    const auto is = static_cast<int>(floor(s_));
    const auto it = static_cast<int>(floor(t_));

    const glm::vec2 f(glm::fract(s_), glm::fract(t_));

    // range [-1;+1]

    const float aa = glm::dot(grad2(is + 0, it + 0, r), f);
    const float ba = glm::dot(grad2(is + 1, it + 0, r), f -glm::vec2(1.f, 0.f));
    const float ab = glm::dot(grad2(is + 0, it + 1, r), f - glm::vec2(0.f, 1.f));
    const float bb = glm::dot(grad2(is + 1, it + 1, r), f - glm::vec2(1.f, 1.f));

    const glm::vec2 i = glm::mix(glm::vec2(aa, ab), glm::vec2(ba, bb), fade(f[0]));

    return glm::mix(i[0], i[1], fade(f[1]));
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type *>
void perlin(tkernel<T> & kernel
    , T scale
    , NoiseType type
    , int startFrequency
    , const int octaves
    , const bool normalize)
{
    const unsigned int size = kernel.width() * kernel.height();

    if(size < 1) 
        return;

    float *temp = new float[size * octaves];
    float *temp2 = new float[size];

    // Generate noise data for each octave.
    for(int f = 0; f < octaves; ++f)
    {

        for (int y = 0; y < kernel.height(); ++y)
            for (int x = 0; x < kernel.width(); ++x)
            {
                float xf = static_cast<float>(x) / kernel.width();
                float yf = static_cast<float>(y) / kernel.height();

                temp[(y * kernel.width()  + x) + size * f] = static_cast<float>(noise2(xf, yf, f + startFrequency));
            }
    }

    // Generate image using noise data.

    float *fo = new float[octaves];

    for(int o = 0; o < octaves; ++o) 
        fo[o] = 1.f / static_cast<float>(1 << o);


    float p, f, po, pf, minp = scale, maxp = 0.;

    for(int i = 0; i < kernel.width() * kernel.height(); ++i) 
    {
        p = 0.f;

        for(int o = 0; o < octaves; ++o) 
        {
            f = fo[o];

            po = temp[i + size * o];
            pf = f * po;

            switch(type)
            {
            case NoiseType::Standard:
                p += o > 0 ? 0.f : po; 
                break;
            case NoiseType::Cloud:
                p += pf; 
                break;
            case NoiseType::CloudAbs:
                p += abs(static_cast<float>(pf)); 
                break;
            case NoiseType::Wood:
                p += (pf * 8.f) - int(pf * 8.f); 
                break;
            case NoiseType::Paper:
                p += po * po * (pf > 0 ? 1.f : -1.f); 
                break;
            };
        }

        p += 0.5;

        if(p > maxp) 
            maxp = p;
        if(p < minp) 
            minp = p;

        temp2[i] = p;
    }

    if(normalize)
    {
        const float invF = scale / (maxp - minp);
        for(int i = 0; i < kernel.width() * kernel.height(); ++i) 
        {
            p = temp2[i];

            p -= minp;
            p *= invF;

            kernel[i] = static_cast<float>(p);
        }
    }
    else
    {
        for(int i = 0; i < kernel.width() * kernel.height(); ++i) 
        {
            p = temp2[i];
            p *= scale;

            kernel[i] = static_cast<float>(p);
        }
    }

    delete[] temp;
    delete[] temp2;
}

} // namespace noise

} // namespace glkernel
