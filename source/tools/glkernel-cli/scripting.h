
#include <cppexpose/reflection/Object.h>

#include <glkernel/Kernel.h>

class KernelObject;

class ScriptingObject : public cppexpose::Object
{
public:
    ScriptingObject();

    void uniform(float range_min, float range_max);
    void shuffle_random();
    cppexpose::Object* createKernel1(int width, int height, int depth);
};

class KernelObject : public cppexpose::Object
{
public:
    KernelObject();

    void print();
    cppexpose::Variant toArray();
    void fromArray(const cppexpose::Variant& array);

protected:
    glkernel::kernel1 m_kernel;
};

void doScripting();
