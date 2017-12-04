#include "scripting.h"

#include <iostream>

#include <glkernel/sequence.h>

#include <cppexpose/variant/Variant.h>
#include <cppexpose/scripting/ScriptContext.h>

void printKernel(const std::array<float, 10>& kernel) {
    for (int i = 0; i < 10; ++i)
    {
        std::cout << kernel[i] << std::endl;
    }
}

void doScripting()
{
    ScriptingObject obj;

    cppexpose::ScriptContext scriptContext;
    scriptContext.addGlobalObject(&obj);

    auto variant = scriptContext.evaluate("kernel.uniform(0.0, 1.0); kernel.print();");
}

ScriptingObject::ScriptingObject()
: Object("kernel")
{
    m_kernel = glkernel::kernel1(10, 1, 1);

    addFunction("uniform", this, &ScriptingObject::uniform);
    addFunction("print", this, &ScriptingObject::print);
}

void ScriptingObject::uniform(float range_min, float range_max)
{
    glkernel::sequence::uniform(m_kernel, range_min, range_max);
}

void ScriptingObject::print()
{
    for (const auto& val : m_kernel)
        std::cout << val << std::endl;
}
