
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
*                                                                             *
*  Started by Ángel on october of 2015                                        *
*                                                                             *
*  This is free software released into the public domain.                     *
*                                                                             *
*  angel.rodriguez@esne.edu                                                   *
*                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SAMPLE_POINT_HEADER
#define SAMPLE_POINT_HEADER

#include <cstddef>
#include <algorithm>

namespace transformations
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

		Point(const std::initializer_list< Numeric_Type > & coordinates)
		{
			std::copy(coordinates.begin(), coordinates.end(), values);
		}

		Point(const Numeric_Type(&coordinates)[dimension])
		{
			for (size_t i = 0; i < dimension; ++i) values[i] = coordinates[i];
		}

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

#endif
