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
        kernel.uniform(0.0, 1.0);
        var t = kernel.toArray();
        t = t.map(function(v) { return Math.log(v + 0.1); });
        kernel.fromArray(t);
        kernel.shuffle_random();
        var s = kernel.toArray();
        s
    )";

    auto variant = scriptContext.evaluate(script);
    std::cout << variant.toString();
}

ScriptingObject::ScriptingObject()
: Object("kernel")
{
    m_kernel = glkernel::kernel1(10, 1, 1);

    addFunction("uniform", this, &ScriptingObject::uniform);
    addFunction("shuffle_random", this, &ScriptingObject::shuffle_random);
    addFunction("print", this, &ScriptingObject::print);
    addFunction("toArray", this, &ScriptingObject::toArray);
    addFunction("fromArray", this, &ScriptingObject::fromArray);
}

void ScriptingObject::uniform(float range_min, float range_max)
{
    glkernel::sequence::uniform(m_kernel, range_min, range_max);
}

void ScriptingObject::shuffle_random()
{
    glkernel::shuffle::random(m_kernel);
}

void ScriptingObject::print()
{
    for (const auto& val : m_kernel)
    {
        std::cout << val << std::endl;
    }
}

cppexpose::Variant ScriptingObject::toArray()
{
    cppexpose::Variant result = cppexpose::Variant::array();
    auto resultArray = result.asArray();

    for (const auto& val : m_kernel)
    {
        resultArray->push_back(val);
    }

    return result;
}

void ScriptingObject::fromArray(const cppexpose::Variant& array)
{
    auto values = array.asArray();

    int i = 0;

    for (const auto& variant : *values)
    {
        m_kernel[i] = variant.value<float>();
        i += 1;
    }
}
