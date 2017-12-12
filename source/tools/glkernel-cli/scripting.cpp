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

    auto script = R"(
        var Kernel = function(x, y, z) {
            this.kernel = _glkernel.createKernel1(x, y, z);
            //this.kernel.print();
        };

        // inherit from Array
        //Kernel.prototype = new Array;

        var kernel = new Kernel(10, 1, 1);
//        kernel.push(1.0);
//        kernel.push(2.0);
//        kernel.push(3.0);

//        kernel
    )";

    auto variant = scriptContext.evaluate(script);
    std::cout << variant.toString();
}

ScriptingObject::ScriptingObject()
: Object("_glkernel")
{
//    addFunction("uniform", this, &ScriptingObject::uniform);
//    addFunction("shuffle_random", this, &ScriptingObject::shuffle_random);
    addFunction("createKernel1", this, &ScriptingObject::createKernel1);
    //addFunction("toArray", this, &ScriptingObject::toArray);
    //addFunction("fromArray", this, &ScriptingObject::fromArray);
}

cppexpose::Object* ScriptingObject::createKernel1(int width, int height, int depth)
{
    std::cout << width << " " << height << " " << depth << std::endl;
    return new KernelObject();
}

//void ScriptingObject::uniform(float range_min, float range_max)
//{
//    glkernel::sequence::uniform(m_kernel, range_min, range_max);
//}

//void ScriptingObject::shuffle_random()
//{
//    glkernel::shuffle::random(m_kernel);
//}

KernelObject::KernelObject()
: Object()
{
    m_kernel = glkernel::kernel1(10, 1, 1);

    addFunction("print", this, &KernelObject::print);
}

cppexpose::Variant KernelObject::toArray()
{
    cppexpose::Variant result = cppexpose::Variant::array();
    auto resultArray = result.asArray();

    for (const auto& val : m_kernel)
    {
        resultArray->push_back(val);
    }

    return result;
}

void KernelObject::fromArray(const cppexpose::Variant& array)
{
    auto values = array.asArray();

    int i = 0;

    for (const auto& variant : *values)
    {
        m_kernel[i] = variant.value<float>();
        i += 1;
    }
}

void KernelObject::print()
{
    std::cout << "I'm a kernel." << std::endl;
}
