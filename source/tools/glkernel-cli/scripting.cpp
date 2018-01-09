#include "scripting.h"

#include <iostream>

#include <glkernel/sequence.h>
#include <glkernel/shuffle.h>
#include <glkernel/scale.h>
#include <glkernel/sort.h>

#include <cppexpose/variant/Variant.h>
#include <cppexpose/scripting/ScriptContext.h>

void doScripting()
{
    ScriptingObject obj;

    cppexpose::ScriptContext scriptContext;
    scriptContext.addGlobalObject(&obj);
    scriptContext.scriptException.connect([](const std::string & msg) {
        std::cerr << msg << std::endl;
    });

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

        // Done with preparation

        var kernel = new Kernel1(10, 1, 1);

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

    )javascript";

    auto variant = scriptContext.evaluate(script);
    std::cout << variant.toString();
}

ScriptingObject::ScriptingObject()
: Object("_glkernel")
{
    addFunction("uniform", this, &ScriptingObject::uniform);
    addFunction("shuffle_random", this, &ScriptingObject::shuffle_random);
    addFunction("scale_range", this, &ScriptingObject::scale_range);
    addFunction("sort_distance", this, &ScriptingObject::sort_distance);

    addFunction("createKernel1", this, &ScriptingObject::createKernel1);
    addFunction("print", this, &ScriptingObject::print);
}

void ScriptingObject::print(std::string s)
{
    std::cout << s << std::endl;
}

cppexpose::Object* ScriptingObject::createKernel1(int width, int height, int depth)
{
    return new Kernel1Object(width, height, depth);
}

cppexpose::Object* ScriptingObject::createKernel2(int width, int height, int depth)
{
    return new Kernel2Object(width, height, depth);
}

cppexpose::Object* ScriptingObject::createKernel3(int width, int height, int depth)
{
    return new Kernel3Object(width, height, depth);
}

cppexpose::Object* ScriptingObject::createKernel4(int width, int height, int depth)
{
    return new Kernel4Object(width, height, depth);
}

void ScriptingObject::uniform(cppexpose::Object* obj, float range_min, float range_max)
{
    if (auto kernelObj = dynamic_cast<Kernel1Object*>(obj))
    {
        glkernel::sequence::uniform(kernelObj->kernel(), range_min, range_max);
        return;
    }

    if (auto kernelObj = dynamic_cast<Kernel2Object*>(obj))
    {
        glkernel::sequence::uniform(kernelObj->kernel(), range_min, range_max);
        return;
    }

    if (auto kernelObj = dynamic_cast<Kernel3Object*>(obj))
    {
        glkernel::sequence::uniform(kernelObj->kernel(), range_min, range_max);
        return;
    }

    if (auto kernelObj = dynamic_cast<Kernel4Object*>(obj))
    {
        glkernel::sequence::uniform(kernelObj->kernel(), range_min, range_max);
        return;
    }

    std::cerr << "Invalid kernel object in uniform()" << std::endl;
}

void ScriptingObject::shuffle_random(cppexpose::Object* obj)
{
    if (auto kernelObj = dynamic_cast<Kernel1Object*>(obj))
    {
        glkernel::shuffle::random(kernelObj->kernel());
        return;
    }

    if (auto kernelObj = dynamic_cast<Kernel2Object*>(obj))
    {
        glkernel::shuffle::random(kernelObj->kernel());
        return;
    }

    if (auto kernelObj = dynamic_cast<Kernel3Object*>(obj))
    {
        glkernel::shuffle::random(kernelObj->kernel());
        return;
    }

    if (auto kernelObj = dynamic_cast<Kernel4Object*>(obj))
    {
        glkernel::shuffle::random(kernelObj->kernel());
        return;
    }

    std::cerr << "Invalid kernel object in shuffle_random()" << std::endl;
}

void ScriptingObject::scale_range(cppexpose::Object* obj, float toMin, float toMax, float fromMin, float fromMax)
{
    if (auto kernelObj = dynamic_cast<Kernel1Object*>(obj))
    {
        glkernel::scale::range(kernelObj->kernel(), toMin, toMax, fromMin, fromMax);
        return;
    }

    if (auto kernelObj = dynamic_cast<Kernel2Object*>(obj))
    {
        glkernel::scale::range(kernelObj->kernel(), toMin, toMax, fromMin, fromMax);
        return;
    }

    if (auto kernelObj = dynamic_cast<Kernel3Object*>(obj))
    {
        glkernel::scale::range(kernelObj->kernel(), toMin, toMax, fromMin, fromMax);
        return;
    }

    if (auto kernelObj = dynamic_cast<Kernel4Object*>(obj))
    {
        glkernel::scale::range(kernelObj->kernel(), toMin, toMax, fromMin, fromMax);
        return;
    }

    std::cerr << "Invalid kernel object in scale_range()" << std::endl;
}

void ScriptingObject::sort_distance(cppexpose::Object* obj, float origin)
{
    if (auto kernelObj = dynamic_cast<Kernel1Object*>(obj))
    {
        glkernel::sort::distance(kernelObj->kernel(), origin);
        return;
    }

    if (auto kernelObj = dynamic_cast<Kernel2Object*>(obj))
    {
        std::cerr << "Invalid origin in sort_distance(): float instead of vec2" << std::endl;
        return;
    }

    if (auto kernelObj = dynamic_cast<Kernel3Object*>(obj))
    {
        std::cerr << "Invalid origin in sort_distance(): float instead of vec3" << std::endl;
        return;
    }

    if (auto kernelObj = dynamic_cast<Kernel4Object*>(obj))
    {
        std::cerr << "Invalid origin in sort_distance(): float instead of vec4" << std::endl;
        return;
    }

    std::cerr << "Invalid kernel object in scale_range()" << std::endl;
}

Kernel1Object::Kernel1Object(int width, int height, int depth)
: Object()
, m_kernel(width, height, depth)
{
}

glkernel::kernel1& Kernel1Object::kernel()
{
	return m_kernel;
}

Kernel2Object::Kernel2Object(int width, int height, int depth)
: Object()
, m_kernel(width, height, depth)
{
}

glkernel::kernel2& Kernel2Object::kernel()
{
	return m_kernel;
}

Kernel3Object::Kernel3Object(int width, int height, int depth)
: Object()
, m_kernel(width, height, depth)
{
}

glkernel::kernel3& Kernel3Object::kernel()
{
	return m_kernel;
}

Kernel4Object::Kernel4Object(int width, int height, int depth)
: Object()
, m_kernel(width, height, depth)
{
}

glkernel::kernel4& Kernel4Object::kernel()
{
	return m_kernel;
}

