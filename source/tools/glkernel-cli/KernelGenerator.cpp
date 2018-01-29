#include "KernelGenerator.h"

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
    // TODO: replace API string with pregenerated API JS file
    auto api = R"javascript(
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
    )javascript";

    return executeScript(api + m_scriptCode);
}
