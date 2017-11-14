#pragma once

#include <cstddef>

namespace DTween
{

	template< size_t DIMENSION, typename NUMERIC_TYPE = float >
	class Point
	{
	public:

		typedef NUMERIC_TYPE Numeric_Type;
		static  const size_t dimension = DIMENSION;

	private:

		Numeric_Type  values[dimension];

	public:

		Numeric_Type & operator [] (size_t index)
		{
			return values[index];
		}

		const Numeric_Type & operator [] (size_t index) const
		{
			return values[index];
		}

	};

	typedef Point< 2, float > Point2f;

	template< typename NUMERIC_TYPE >
	inline Point< 2, NUMERIC_TYPE > make_point2(NUMERIC_TYPE x, NUMERIC_TYPE y)
	{
		Point< 2, NUMERIC_TYPE > result;
		result[0] = x;
		result[1] = y;
		return result;
	}

	inline Point2f make_point2f(float x, float y)
	{
		return make_point2< float >(x, y);
	}

}