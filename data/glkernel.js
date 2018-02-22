
// THIS IS A GENERATED FILE!
// DO NOT EDIT

GradientNoiseType = {
    Perlin: 0,
    Simplex: 1
};

HemisphereMapping = {
    Uniform: 0,
    Cosine: 1
};

OctaveType = {
    Standard: 0,
    Cloud: 1,
    CloudAbs: 2,
    Wood: 3,
    Paper: 4
};

var _Kernel = function(x,y,z) {
    this._initialize = function(x,y,z) {
        var that = this;

        this.kernel = this.generateKernel(x,y,z);

        this.noise = {
            uniform: function(range_min, range_max) {
                _glkernel.noise_uniform(that.kernel, range_min, range_max);
                return that;
            },
            normal: function(mean, stddev) {
                _glkernel.noise_normal(that.kernel, mean, stddev);
                return that;
            },
            gradient: function(noise_type, octave_type, startFrequency, octaves) {
                // Defaults
                noise_type = (typeof noise_type !== 'undefined') ? noise_type : GradientNoiseType.Perlin;
                octave_type = (typeof octave_type !== 'undefined') ? octave_type : OctaveType.Standard;
                startFrequency = (typeof startFrequency !== 'undefined') ? startFrequency : 3;
                octaves = (typeof octaves !== 'undefined') ? octaves : 5;

                _glkernel.noise_gradient(that.kernel, noise_type, octave_type, startFrequency, octaves);
                return that;
            }
        };
        this.sample = {
            poisson_square: function(num_probes) {
                // Defaults
                num_probes = (typeof num_probes !== 'undefined') ? num_probes : 32;

                _glkernel.sample_poisson_square(that.kernel, num_probes);
                return that;
            },
            poisson_square: function(min_dist, num_probes) {
                // Defaults
                num_probes = (typeof num_probes !== 'undefined') ? num_probes : 32;

                _glkernel.sample_poisson_square1(that.kernel, min_dist, num_probes);
                return that;
            },
            stratified: function() {
                _glkernel.sample_stratified(that.kernel);
                return that;
            },
            hammersley: function() {
                _glkernel.sample_hammersley(that.kernel);
                return that;
            },
            halton: function(base1, base2) {
                _glkernel.sample_halton(that.kernel, base1, base2);
                return that;
            },
            hammersley_sphere: function(type) {
                // Defaults
                type = (typeof type !== 'undefined') ? type : HemisphereMapping.Uniform;

                _glkernel.sample_hammersley_sphere(that.kernel, type);
                return that;
            },
            halton_sphere: function(base1, base2, type) {
                // Defaults
                type = (typeof type !== 'undefined') ? type : HemisphereMapping.Uniform;

                _glkernel.sample_halton_sphere(that.kernel, base1, base2, type);
                return that;
            },
            best_candidate: function(num_candidates) {
                // Defaults
                num_candidates = (typeof num_candidates !== 'undefined') ? num_candidates : 32;

                _glkernel.sample_best_candidate(that.kernel, num_candidates);
                return that;
            },
            n_rooks: function() {
                _glkernel.sample_n_rooks(that.kernel);
                return that;
            },
            multi_jittered: function(correlated) {
                // Defaults
                correlated = (typeof correlated !== 'undefined') ? correlated : false;

                _glkernel.sample_multi_jittered(that.kernel, correlated);
                return that;
            },
            golden_point_set: function() {
                _glkernel.sample_golden_point_set(that.kernel);
                return that;
            }
        };
        this.scale = {
            range: function(rangeToLower, rangeToUpper, rangeFromLower, rangeFromUpper) {
                // Defaults
                rangeFromLower = (typeof rangeFromLower !== 'undefined') ? rangeFromLower : 0;
                rangeFromUpper = (typeof rangeFromUpper !== 'undefined') ? rangeFromUpper : 1;

                _glkernel.scale_range(that.kernel, rangeToLower, rangeToUpper, rangeFromLower, rangeFromUpper);
                return that;
            }
        };
        this.sequence = {
            uniform: function(range_min, range_max) {
                _glkernel.sequence_uniform(that.kernel, range_min, range_max);
                return that;
            }
        };
        this.shuffle = {
            bucket_permutate: function(subkernel_width, subkernel_height, subkernel_depth, permutate_per_bucket) {
                // Defaults
                subkernel_width = (typeof subkernel_width !== 'undefined') ? subkernel_width : 1;
                subkernel_height = (typeof subkernel_height !== 'undefined') ? subkernel_height : 1;
                subkernel_depth = (typeof subkernel_depth !== 'undefined') ? subkernel_depth : 1;
                permutate_per_bucket = (typeof permutate_per_bucket !== 'undefined') ? permutate_per_bucket : false;

                _glkernel.shuffle_bucket_permutate(that.kernel, subkernel_width, subkernel_height, subkernel_depth, permutate_per_bucket);
                return that;
            },
            bayer: function() {
                _glkernel.shuffle_bayer(that.kernel);
                return that;
            },
            random: function(start) {
                // Defaults
                start = (typeof start !== 'undefined') ? start : 1;

                _glkernel.shuffle_random(that.kernel, start);
                return that;
            }
        };
        this.sort = {
            distance: function(origin) {
                _glkernel.sort_distance(that.kernel, origin);
                return that;
            }
        };
    };
};

var Kernel1 = function(x,y,z) {
    this.generateKernel = function(x,y,z) {
        return _glkernel.createKernel1(x,y,z);
    }
    this._initialize(x,y,z);
};

var Kernel2 = function(x,y,z) {
    this.generateKernel = function(x,y,z) {
        return _glkernel.createKernel2(x,y,z);
    }
    this._initialize(x,y,z);
};

var Kernel3 = function(x,y,z) {
    this.generateKernel = function(x,y,z) {
        return _glkernel.createKernel3(x,y,z);
    }
    this._initialize(x,y,z);
};

var Kernel4 = function(x,y,z) {
    this.generateKernel = function(x,y,z) {
        return _glkernel.createKernel4(x,y,z);
    }
    this._initialize(x,y,z);
};

Kernel1.prototype = new _Kernel;
Kernel2.prototype = new _Kernel;
Kernel3.prototype = new _Kernel;
Kernel4.prototype = new _Kernel;
