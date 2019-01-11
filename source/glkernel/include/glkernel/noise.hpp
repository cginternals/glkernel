
#pragma once

#include <glkernel/noise.h>

#include <glkernel/glm_compatability.h>


namespace
{


// From // JAVA REFERENCE IMPLEMENTATION OF IMPROVED NOISE - COPYRIGHT 2002 KEN PERLIN. (http://mrl.nyu.edu/~perlin/noise/)
// and (Improving Noise - Perlin - 2002) - http://mrl.nyu.edu/~perlin/paper445.pdf

const std::vector<unsigned char> perm =
{
    151, 160, 137,  91,  90,  15, 131,  13, 201,  95,  96,  53, 194, 233,   7, 225,
    140,  36, 103,  30,  69, 142,   8,  99,  37, 240,  21,  10,  23, 190,   6, 148,
    247, 120, 234,  75,   0,  26, 197,  62,  94, 252, 219, 203, 117,  35,  11,  32,
     57, 177,  33,  88, 237, 149,  56,  87, 174,  20, 125, 136, 171, 168,  68, 175,
     74, 165,  71, 134, 139,  48,  27, 166,  77, 146, 158, 231,  83, 111, 229, 122,
     60, 211, 133, 230, 220, 105,  92,  41,  55,  46, 245,  40, 244, 102, 143,  54,
     65,  25,  63, 161,   1, 216,  80,  73, 209,  76, 132, 187, 208,  89,  18, 169,
    200, 196, 135, 130, 116, 188, 159,  86, 164, 100, 109, 198, 173, 186,   3,  64,
     52, 217, 226, 250, 124, 123,   5, 202,  38, 147, 118, 126, 255,  82,  85, 212,
    207, 206,  59, 227,  47,  16,  58,  17, 182, 189,  28,  42, 223, 183, 170, 213,
    119, 248, 152,   2,  44, 154, 163,  70, 221, 153, 101, 155, 167,  43, 172,   9,
    129,  22,  39, 253,  19,  98, 108, 110,  79, 113, 224, 232, 178, 185, 112, 104,
    218, 246,  97, 228, 251,  34, 242, 193, 238, 210, 144,  12, 191, 179, 162, 241,
     81,  51, 145, 235, 249,  14, 239, 107,  49, 192, 214,  31, 181, 199, 106, 157,
    184,  84, 204, 176, 115, 121,  50,  45, 127,   4, 150, 254, 138, 236, 205,  93,
    222, 114,  67,  29,  24,  72, 243, 141, 128, 195,  78,  66, 215,  61, 156, 180
};

const std::vector<glm::vec3> grad =
{
    { 1.0, 1.0, 0.0 }, { -1.0, 1.0, 0.0 }, { 1.0, -1.0, 0.0 }, { -1.0, -1.0, 0.0 },
    { 1.0, 0.0, 1.0 }, { -1.0, 0.0, 1.0 }, { 1.0, 0.0, -1.0 }, { -1.0, 0.0, -1.0 },
    { 0.0, 1.0, 1.0 }, { 0.0, -1.0, 1.0 }, { 0.0, 1.0, -1.0 }, { 0.0, -1.0, -1.0 },
    { 1.0, 1.0, 0.0 }, { -1.0, 1.0, 0.0 }, { 0.0, -1.0, 0.0 }, { 0.0, -1.0, -1.0 }
};

unsigned char hash3(
    const unsigned int x
    , const unsigned int y
    , const unsigned int z
    , const unsigned int r)
{
    // the values of x, y and z will be in [0, 1 << r]
    // the frequency mask is used for returning equal values
    // for the minimum and the maximum input to ensure tileability
    unsigned int frequencyMask = 1 << r;
    assert(frequencyMask <= perm.size());
    return perm[(perm[(perm[x % frequencyMask] + y) % frequencyMask] + z) % frequencyMask];
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
glm::tvec3<T, glm::highp> grad3(
    const unsigned int x
    , const unsigned int y
    , const unsigned int z
    , const unsigned int r)
{
    const auto p = hash3(x, y, z, r);
    return glm::tvec3<T, glm::highp>(grad[p % 16]);
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
glm::tvec3<T, glm::highp> grad3(
    glm::tvec3<unsigned int, glm::highp> v
    , const unsigned int r)
{
    const auto p = hash3(v.x, v.y, v.z, r);
    return glm::tvec3<T, glm::highp>(grad[p % 16]);
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
T smootherstep(const T t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
T perlin3(
    const T s
    , const T t
    , const T u
    , const unsigned int r)
{
    // scale according to frequency
    const auto scaled_s = s * (1 << r);
    const auto scaled_t = t * (1 << r);
    const auto scaled_u = u * (1 << r);

    const auto is = static_cast<unsigned int>(floor(scaled_s));
    const auto it = static_cast<unsigned int>(floor(scaled_t));
    const auto iu = static_cast<unsigned int>(floor(scaled_u));

    const auto f = glm::fract(glm::tvec3<T, glm::highp>(scaled_s, scaled_t, scaled_u));

    // range [-1;+1]

    const auto aaa = glm::dot(grad3<T>(is + 0, it + 0, iu + 0, r), f);
    const auto baa = glm::dot(grad3<T>(is + 1, it + 0, iu + 0, r), f - glm::tvec3<T, glm::highp>(1., 0., 0.));
    const auto aba = glm::dot(grad3<T>(is + 0, it + 1, iu + 0, r), f - glm::tvec3<T, glm::highp>(0., 1., 0.));
    const auto bba = glm::dot(grad3<T>(is + 1, it + 1, iu + 0, r), f - glm::tvec3<T, glm::highp>(1., 1., 0.));
    const auto aab = glm::dot(grad3<T>(is + 0, it + 0, iu + 1, r), f - glm::tvec3<T, glm::highp>(0., 0., 1.));
    const auto bab = glm::dot(grad3<T>(is + 1, it + 0, iu + 1, r), f - glm::tvec3<T, glm::highp>(1., 0., 1.));
    const auto abb = glm::dot(grad3<T>(is + 0, it + 1, iu + 1, r), f - glm::tvec3<T, glm::highp>(0., 1., 1.));
    const auto bbb = glm::dot(grad3<T>(is + 1, it + 1, iu + 1, r), f - glm::tvec3<T, glm::highp>(1., 1., 1.));

    // interpolate noise values of the eight corners
    const auto i = glm::mix(
        glm::tvec4<T, glm::highp>(aaa, aab, aba, abb),
        glm::tvec4<T, glm::highp>(baa, bab, bba, bbb),
        smootherstep(f[0]));
    const auto j = glm::mix(
        glm::tvec2<T, glm::highp>(i[0], i[1]),
        glm::tvec2<T, glm::highp>(i[2], i[3]),
        smootherstep(f[1]));

    return glm::mix(j[0], j[1], smootherstep(f[2]));
}

// adapted from example code by Stefan Gustavson (stegu@itn.liu.se)
// (http://webstaff.itn.liu.se/~stegu/simplexnoise/SimplexNoise.java)
template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
T simplex3(
    const T s
    , const T t
    , const T u
    , const unsigned int r)
{
    const T skew_constant = 1 / static_cast<T>(3);
    const T unskew_constant = 1 / static_cast<T>(6);
    // scale according to frequency
    const glm::tvec3<T, glm::highp> pos = {s, t, u};
    const glm::tvec3<T, glm::highp> scaled_pos = pos * static_cast<T>(1 << r);
    // skew the input space to determine the simplex cell origin
    const T skew_factor = (scaled_pos.x + scaled_pos.y + scaled_pos.z) * skew_constant;
    const glm::tvec3<unsigned int, glm::highp> corner = glm::tvec3<unsigned int, glm::highp>(glm::floor(scaled_pos + skew_factor));
    // unskew the cell origin back to (x,y,z) space
    const T unskew_factor = (corner.x + corner.y + corner.z) * unskew_constant;
    const glm::tvec3<T, glm::highp> v0 = scaled_pos + unskew_factor - static_cast<glm::tvec3<T, glm::highp>>(corner);
    // for the 3D case, the simplex shape is a slightly irregular tetrahedron.
    // determine corner offsets in skewed space for specific simplex
    glm::tvec3<unsigned int, glm::highp> corner_offset1;
    glm::tvec3<unsigned int, glm::highp> corner_offset2;
    if (v0.x >= v0.y)
    {
        if (v0.y >= v0.z)
        {
            corner_offset1 = {1, 0, 0};
            corner_offset2 = {1, 1, 0};
        } // X Y Z order
        else if (v0.x >= v0.z)
        {
            corner_offset1 = {1, 0, 0};
            corner_offset2 = {1, 0, 1};
        } // X Z Y order
        else
        {
            corner_offset1 = {0, 0, 1};
            corner_offset2 = {1, 0, 1};
        } // Z X Y order
    }
    else
    { // v0.x < v0.y
        if (v0.y < v0.z)
        {
            corner_offset1 = {0, 0, 1};
            corner_offset2 = {0, 1, 1};
        } // Z Y X order
        else if (v0.x < v0.z)
        {
            corner_offset1 = {0, 1, 0};
            corner_offset2 = {0, 1, 1};
        } // Y Z X order
        else
        {
            corner_offset1 = {0, 1, 0};
            corner_offset2 = {1, 1, 0};
        } // Y X Z order
    }
    // corner offsets in (x,y,z) space
    const glm::tvec3<T, glm::highp> v1 = v0 +      unskew_constant - static_cast<glm::tvec3<T, glm::highp>>(corner_offset1);
    const glm::tvec3<T, glm::highp> v2 = v0 +  2 * unskew_constant - static_cast<glm::tvec3<T, glm::highp>>(corner_offset2);
    const glm::tvec3<T, glm::highp> v3 = v0 + (3 * unskew_constant - 1);
    // contribution factors
    const T t0 = static_cast<T>(0.5) - glm::dot(v0, v0);
    const T t1 = static_cast<T>(0.5) - glm::dot(v1, v1);
    const T t2 = static_cast<T>(0.5) - glm::dot(v2, v2);
    const T t3 = static_cast<T>(0.5) - glm::dot(v3, v3);
    // Calculate the contribution from the four corners
    const T n0 = (t0 < 0) ? 0 : (std::pow(t0, 4) * glm::dot(grad3<T>(corner,                  r), v0));
    const T n1 = (t1 < 0) ? 0 : (std::pow(t1, 4) * glm::dot(grad3<T>(corner + corner_offset1, r), v1));
    const T n2 = (t2 < 0) ? 0 : (std::pow(t2, 4) * glm::dot(grad3<T>(corner + corner_offset2, r), v2));
    const T n3 = (t3 < 0) ? 0 : (std::pow(t3, 4) * glm::dot(grad3<T>(corner + 1u,             r), v3));
    // Add contributions from each corner to get the final noise value.
    // The result is scaled to stay just inside [-1,1]
    return 32 * (n0 + n1 + n2 + n3);
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
T get_octave_type_value(const glkernel::noise::OctaveType type
    , const unsigned int octave
    , const T noise_value
    , const T octaved_noise)
{
    switch (type)
    {
    case glkernel::noise::OctaveType::Standard:
        return octave > 0 ? 0 : noise_value;
    case glkernel::noise::OctaveType::Cloud:
        return octaved_noise;
    case glkernel::noise::OctaveType::CloudAbs:
        return fabs(octaved_noise);
    case glkernel::noise::OctaveType::Wood:
        return octaved_noise * 8 - static_cast<int>(octaved_noise * 8);
    case glkernel::noise::OctaveType::Paper:
        return noise_value * noise_value * static_cast<T>(octaved_noise > 0 ? 1 : -1);
    default:
        return noise_value;
    }
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
T get_noise_type_value(const glkernel::noise::GradientNoiseType type
    , const T x
    , const T y
    , const T z
    , const unsigned int octave)
{
    switch (type)
    {
    case glkernel::noise::GradientNoiseType::Perlin:
        return perlin3(x, y, z, octave);
    case glkernel::noise::GradientNoiseType::Simplex:
        return simplex3(x, y, z, octave);
    default:
        return 0;
    }
}


} // namespace


namespace glkernel
{


namespace noise
{


template <typename T>
class uniform_operator
{
public:
    template<typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
    uniform_operator(size_t size, glm::length_t
        , T range_min, T range_max);

    template<typename V, typename std::enable_if<std::is_floating_point<typename V::value_type>::value>::type * = nullptr>
    uniform_operator(size_t size, glm::length_t coefficient
        , const V & range_min, const V & range_max);

    T operator()(const size_t index);

protected:
    std::mt19937_64 m_generator;
    std::uniform_real_distribution<T> m_distribute;
};


template<typename T>
template<typename std::enable_if<std::is_floating_point<T>::value>::type *>
uniform_operator<T>::uniform_operator(const size_t, const glm::length_t
    , const T range_min, const T range_max)
: m_generator{ std::random_device{ }() }
, m_distribute{ range_min, range_max }
{
}

template <typename T>
template<typename V, typename std::enable_if<std::is_floating_point<typename V::value_type>::value>::type *>
uniform_operator<T>::uniform_operator(const size_t size, const glm::length_t coefficient
    , const V & range_min, const V & range_max)
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
    kernel.template for_each<uniform_operator<T>>(range_min, range_max);
}

template<typename V, typename std::enable_if<std::is_floating_point<typename V::value_type>::value>::type *>
void uniform(tkernel<V> & kernel, const typename V::value_type range_min, const typename V::value_type range_max)
{
    kernel.template for_each<uniform_operator<typename V::value_type>>(range_min, range_max);
}

template <typename V, typename std::enable_if<std::is_floating_point<typename V::value_type>::value>::type * = nullptr>
void uniform(tkernel<V> & kernel, const V & range_min, const V & range_max)
{
    kernel.template for_each<uniform_operator<typename V::value_type>>(range_min, range_max);
}


template <typename T>
class normal_operator
{
public:
    template <typename std::enable_if<std::is_floating_point<T>::value>::type * = nullptr>
    normal_operator(size_t size, glm::length_t
        , T mean, T stddev);

    template <typename V, typename std::enable_if<std::is_floating_point<typename V::value_type>::value>::type * = nullptr>
    normal_operator(size_t size, glm::length_t coefficient
        , const V & mean, const V & stddev);

    T operator()(const size_t index);

protected:
    std::mt19937_64 m_generator;
    std::uniform_real_distribution<T> m_distribute;
};


template <typename T>
template <typename std::enable_if<std::is_floating_point<T>::value>::type *>
normal_operator<T>::normal_operator(const size_t, const glm::length_t
    , const T mean, const T stddev)
: m_generator{ std::random_device{}() }
, m_distribute{ mean, stddev }
{
}

template <typename T>
template <typename V, typename std::enable_if<std::is_floating_point<typename V::value_type>::value>::type *>
normal_operator<T>::normal_operator(const size_t size, const glm::length_t coefficient
    , const V & mean, const V & stddev)
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
    kernel.template for_each<normal_operator<T>>(mean, stddev);
}

template <typename V, typename std::enable_if<std::is_floating_point<typename V::value_type>::value>::type * = nullptr>
void normal(tkernel<V> & kernel, const typename V::value_type mean, const typename V::value_type stddev)
{
    kernel.template for_each<normal_operator<typename V::value_type>>(mean, stddev);
}

template <typename V, typename std::enable_if<std::is_floating_point<typename V::value_type>::value>::type * = nullptr>
void normal(tkernel<V> & kernel, const V & mean, const V & stddev)
{
    kernel.template for_each<normal_operator<typename V::value_type>>(mean, stddev);
}

template<typename T, typename std::enable_if<std::is_floating_point<T>::value>::type *>
void gradient(tkernel<T> & kernel
    , const GradientNoiseType noise_type
    , const OctaveType octave_type
    , const unsigned int start_frequency
    , const unsigned int octaves)
{
    if (kernel.size() < 1)
        return;

    std::vector<T> fo(octaves);

    for (unsigned int o = 0; o < octaves; ++o)
    {
        fo[o] = static_cast<T>(1.0 / (1 << o));
    }

    #pragma omp parallel for
    for (long long i = 0; i < static_cast<long long>(kernel.size()); ++i)
    {
        const auto location = static_cast<glm::tvec3<T, glm::highp>>(kernel.position(i));
        const auto x = location.x / kernel.width();
        const auto y = location.y / kernel.height();
        const auto z = location.z / kernel.depth();

        // collect noise values over multiple octaves
        T p = 0.5;
        for (unsigned int o = 0; o < octaves; ++o)
        {
            const T po = get_noise_type_value(noise_type, x, y, z, o + start_frequency);
            const T pf = fo[o] * po;

            p += get_octave_type_value(octave_type, o, po, pf);
        }

        kernel[i] = p;
    }
}


} // namespace noise


} // namespace glkernel
