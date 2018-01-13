#include "KernelGenerator.hpp"
#include "scripting.h"

#include <glkernel/Kernel.h>
#include <glkernel/noise.h>
#include <glkernel/sort.h>

#include <string>
#include <fstream>
#include <sstream>

KernelGenerator::KernelGenerator(const std::string& inputFileName)
{
    auto inputStream = std::ifstream{inputFileName};
    auto inputStringStream = std::stringstream{};
    inputStringStream << inputStream.rdbuf();
    m_scriptCode = inputStringStream.str();
}

cppexpose::Variant KernelGenerator::generateKernelFromJavascript()
{
    // TODO use m_scriptCode
    auto script = R"javascript(
        var _Kernel = function(x,y,z) {
            this._initialize = function(x,y,z) {
                var that = this;

                this.kernel = this.generateKernel(x,y,z);

                this.sequence = {
                    uniform: function(min, max) {
                        _glkernel.uniform(that.kernel, min, max);
                    }
                };
                this.shuffle = {
                    random: function() {
                        _glkernel.shuffle_random(that.kernel);
                    }
                };
                this.scale = {
                    range: function(toMin, toMax, fromMin, fromMax) {
                        // Defining default values for some parameters
                        fromMin = (typeof fromMin !== 'undefined') ? fromMin : 0.0;
                        fromMax = (typeof fromMax !== 'undefined') ? fromMax : 1.0;

                        _glkernel.scale_range(that.kernel, toMin, toMax, fromMin, fromMax);
                    }
                };
                this.sort = {
                    distance: function(origin) {
                        _glkernel.sort_distance(that.kernel, origin);
                    }
                };
            };
        };

        var Kernel1 = function(x,y,z) {
            this.generateKernel = function(x,y,z) {
                return _glkernel.createKernel1(x,y,z);
            }
            this._initialize(x,y,z);
        }

        Kernel1.prototype = new _Kernel;

        var Kernel2 = function(x,y,z) {
            this.generateKernel = function(x,y,z) {
                return _glkernel.createKernel2(x,y,z);
            }
            this._initialize(x,y,z);
        }

        Kernel2.prototype = new _Kernel;

        // Done with preparation

        var kernel = new Kernel2(10, 5, 2);

        kernel.sequence.uniform(0.0, 1.0);
        kernel.shuffle.random();
        kernel.scale.range(-1,1);
        kernel.sort.distance(0);

        f = function(arg) {
            if (typeof arg === "number")
                return "float";

            if (typeof arg === "object") {
                var keys = Object.keys(arg);
                if ("0" in keys && typeof arg[0] === "number") {
                    if ("1" in keys && typeof arg[1] === "number") {
                        if ("2" in keys && typeof arg[2] === "number") {
                            if ("3" in keys && typeof arg[3] === "number")
                                return "vec4";
                            else
                                return "vec3";
                        }
                        else
                            return "vec2";
                    }
                    else
                        return "vec1";
                }
            }

            return "unknown";
        }

        _glkernel.print(f(1));                   // float
        _glkernel.print(f([1]));                 // vec1
        _glkernel.print(f([1,2]));               // vec2
        _glkernel.print(f([1,2,3]));             // vec3
        _glkernel.print(f([1,2,3,4]));           // vec4
        _glkernel.print(f(["wrong"]));           // unknown
        _glkernel.print(f([1,2,"wrong later"])); // vec2
        _glkernel.print(f("completely wrong"));  // unknown

        kernel.kernel;

    )javascript";

    return executeScript(script);
}
