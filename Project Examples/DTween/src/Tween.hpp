/*

*/

#pragma once

#include "Point.hpp"

namespace DTween {

	template< size_t DIMENSION, typename NUMERIC_TYPE = float >
	class Tween {
	public:

		typedef NUMERIC_TYPE Numeric_Type;
		static  const size_t dimension = DIMENSION;
		typedef Point< dimension, Numeric_Type > Point;

	public:

		virtual Point sample(Numeric_Type t) const = 0;
	};
}