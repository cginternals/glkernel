#include "scripting.h"

#include <iostream>

#include <glkernel/sequence.h>
#include <glkernel/shuffle.h>

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
            };
        };

        var Kernel1 = function(x,y,z) {
            this.generateKernel = function(x,y,z) {
                return _glkernel.createKernel1(x,y,z);
            }
            this._initialize(x,y,z);
        }

        // inherit from Array
        Kernel1.prototype = new _Kernel;

        var kernel = new Kernel1(10, 1, 1);
        kernel.sequence.uniform(0.0, 1.0);
        kernel.shuffle.random();
//        kernel.push(1.0);
//        kernel.push(2.0);
//        kernel.push(3.0);

//        kernel
    )javascript";

    auto variant = scriptContext.evaluate(script);
    std::cout << variant.toString();
}

ScriptingObject::ScriptingObject()
: Object("_glkernel")
{
    addFunction("uniform", this, &ScriptingObject::uniform);
    addFunction("shuffle_random", this, &ScriptingObject::shuffle_random);
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

