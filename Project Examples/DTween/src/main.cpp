/*

*/

#include "Point.hpp"
#include "Tween.hpp"

using namespace DTween;

int main() {

	Point2f origin = make_point2f(100, 100);
	Point2f attractor1 = make_point2f(100, 400);
	Point2f attractor2 = make_point2f(700, 200);
	Point2f ending = make_point2f(700, 500);

	return 0;
}