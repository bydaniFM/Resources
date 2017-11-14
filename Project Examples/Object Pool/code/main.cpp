
#include "Memory_Pool.hpp"
#include "Object_Pool.hpp"

using lib::Memory_Pool;
using lib::Object_Pool;

struct Point3d
{
	float x, y, z;
};

int main ()
{
	//Point3d * point = new Point3d;

	Memory_Pool memory_pool(10*1024*1024);

	Object_Pool< Point3d > object_pool(10000);


	Point3d * point1 = memory_pool.allocate< Point3d >();
	Point3d * point2 = memory_pool.allocate< Point3d >();

	//Point3d * point3 = object_pool.allocate ();
	
	//object_pool.free (point3);

	return 0;
}
