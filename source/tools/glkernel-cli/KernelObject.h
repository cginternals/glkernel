
#include <cppexpose/reflection/Object.h>

#include <glkernel/Kernel.h>


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
