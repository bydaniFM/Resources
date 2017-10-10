/*
Autor: Daniel Fernández
Date: 10/10/2017
*/

#include <iostream>
#include "Vector.hpp"

using namespace example;
using namespace std;

int main() {

	Vector< int, 3 > vector3i({ 0, 0, 0 });
	Vector< float, 3 > vector3f(vector3i);

	float f = vector3f;

	return 0;
}
