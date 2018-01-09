
#include <cppexpose/reflection/Object.h>

#include <glkernel/Kernel.h>

class ScriptingObject : public cppexpose::Object
{
public:
    ScriptingObject();

    void uniform(cppexpose::Object* kernelObj, float range_min, float range_max);
    void shuffle_random(cppexpose::Object* kernelObj);
    void scale_range(cppexpose::Object* kernelObj, float toMin, float toMax, float fromMin = 0.0f, float fromMax = 1.0f);
    void sort_distance(cppexpose::Object* kernelObj, float origin);

    cppexpose::Object* createKernel1(int width, int height, int depth);
    cppexpose::Object* createKernel2(int width, int height, int depth);
    cppexpose::Object* createKernel3(int width, int height, int depth);
    cppexpose::Object* createKernel4(int width, int height, int depth);

    void print(std::string s);
};

class Kernel1Object : public cppexpose::Object
{
public:
    Kernel1Object(int width, int height, int depth);
	glkernel::kernel1& kernel();

protected:
    glkernel::kernel1 m_kernel;
};

class Kernel2Object : public cppexpose::Object
{
public:
    Kernel2Object(int width, int height, int depth);
	glkernel::kernel2& kernel();

protected:
    glkernel::kernel2 m_kernel;
};

class Kernel3Object : public cppexpose::Object
{
public:
    Kernel3Object(int width, int height, int depth);
	glkernel::kernel3& kernel();

protected:
    glkernel::kernel3 m_kernel;
};

class Kernel4Object : public cppexpose::Object
{
public:
    Kernel4Object(int width, int height, int depth);
	glkernel::kernel4& kernel();

protected:
    glkernel::kernel4 m_kernel;
};

void doScripting();
