
// THIS IS A GENERATED FILE!
// DO NOT EDIT

#include <cppexpose/reflection/Object.h>

#include <glkernel/Kernel.h>

class JSInterface : public cppexpose::Object
{
public:
    JSInterface();

    cppexpose::Object* createKernel1(int width, int height, int depth);
    cppexpose::Object* createKernel2(int width, int height, int depth);
    cppexpose::Object* createKernel3(int width, int height, int depth);
    cppexpose::Object* createKernel4(int width, int height, int depth);

    void noise_uniform(cppexpose::Object* obj, const cppexpose::Variant& range_min, const cppexpose::Variant& range_max);
    void noise_normal(cppexpose::Object* obj, const cppexpose::Variant& mean, const cppexpose::Variant& stddev);
    void noise_gradient(cppexpose::Object* obj, int noise_type, int octave_type, unsigned int startFrequency, unsigned int octaves);
    void sample_poisson_square(cppexpose::Object* obj, unsigned int num_probes);
    void sample_poisson_square1(cppexpose::Object* obj, float min_dist, unsigned int num_probes);
    void sample_stratified(cppexpose::Object* obj);
    void sample_hammersley(cppexpose::Object* obj);
    void sample_halton(cppexpose::Object* obj, unsigned int base1, unsigned int base2);
    void sample_hammersley_sphere(cppexpose::Object* obj, int type);
    void sample_halton_sphere(cppexpose::Object* obj, unsigned int base1, unsigned int base2, int type);
    void sample_best_candidate(cppexpose::Object* obj, unsigned int num_candidates);
    void sample_n_rooks(cppexpose::Object* obj);
    void sample_multi_jittered(cppexpose::Object* obj, bool correlated);
    void sample_golden_point_set(cppexpose::Object* obj);
    void scale_range(cppexpose::Object* obj, float rangeToLower, float rangeToUpper, float rangeFromLower, float rangeFromUpper);
    void sequence_uniform(cppexpose::Object* obj, const cppexpose::Variant& range_min, const cppexpose::Variant& range_max);
    void shuffle_bucket_permutate(cppexpose::Object* obj, glm::uint16 subkernel_width, glm::uint16 subkernel_height, glm::uint16 subkernel_depth, bool permutate_per_bucket);
    void shuffle_bayer(cppexpose::Object* obj);
    void shuffle_random(cppexpose::Object* obj, size_t start);
    void sort_distance(cppexpose::Object* obj, const cppexpose::Variant& origin);
};
