
#include <cppexpose/reflection/Object.h>

#include <glkernel/Kernel.h>

class ScriptingObject : public cppexpose::Object
{
public:
    ScriptingObject();

    void uniform(float range_min, float range_max);
    void print();

protected:
    glkernel::kernel1 m_kernel;
};

void doScripting();
