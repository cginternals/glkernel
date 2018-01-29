#ifdef __BULLSHIT__
#include "KernelObject.h"


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
#endif