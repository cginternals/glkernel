#include "scripting.h"

#include <iostream>

#include <glkernel/sequence.h>
#include <glkernel/shuffle.h>
#include <glkernel/scale.h>
#include <glkernel/sort.h>

#include <cppexpose/variant/Variant.h>
#include <cppexpose/scripting/ScriptContext.h>

cppexpose::Variant executeScript(const std::string & script)
{
    ScriptingObject obj;

    cppexpose::ScriptContext scriptContext;
    scriptContext.addGlobalObject(&obj);
    scriptContext.scriptException.connect([](const std::string & msg) {
        std::cerr << msg << std::endl;
    });

    auto variant = scriptContext.evaluate(script);
    std::cout << variant.type().name() << std::endl;
    if (variant.hasType<cppexpose::Object*>())
    {
        auto kernelObject = variant.value<cppexpose::Object*>();

        auto kernel1Object = dynamic_cast<Kernel1Object*>(kernelObject);
        if (kernel1Object)
        {
            cppexpose::Variant::fromValue(kernel1Object->kernel());
        }

        auto kernel2Object = dynamic_cast<Kernel2Object*>(kernelObject);
        if (kernel2Object)
        {
            cppexpose::Variant::fromValue(kernel2Object->kernel());
        }
    }
    return variant;
}

ScriptingObject::ScriptingObject()
: Object("_glkernel")
{
    addFunction("uniform", this, &ScriptingObject::uniform);
    addFunction("shuffle_random", this, &ScriptingObject::shuffle_random);
    addFunction("scale_range", this, &ScriptingObject::scale_range);
    addFunction("sort_distance", this, &ScriptingObject::sort_distance);

    addFunction("createKernel1", this, &ScriptingObject::createKernel1);
    addFunction("createKernel2", this, &ScriptingObject::createKernel2);
    addFunction("createKernel3", this, &ScriptingObject::createKernel3);
    addFunction("createKernel4", this, &ScriptingObject::createKernel4);

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
