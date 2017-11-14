
#include "Memory_Pool.hpp"

using lib::Memory_Pool;

struct Point3d
{
	float x, y, z;
};

int main ()
{
	//Point3d * point = new Point3d;

	Memory_Pool memory_pool(10*1024*1024);

	Point3d * point = memory_pool.allocate< Point3d >();

	return 0;
}
