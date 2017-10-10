/*
Autor: Ángel
Fecha: 3.oct.2017
*/

#pragma once

#include <cmath>
#include <cstddef>

namespace example
{

	template< typename TYPE, size_t SIZE >
	class Vector
	{

		static_assert(SIZE > 0);

		TYPE values[SIZE];

	public:

		Vector() = default;
		Vector(const Vector & other) = default;

		template< typename OTHER_TYPE >
		explicit Vector(const Vector< OTHER_TYPE, SIZE > & other)
		{
			for (size_t i = 0; i < SIZE; ++i)
			{
				values[i] = static_cast< TYPE >(other[i]);
			}
		}

		Vector(const TYPE (&array)[SIZE])
		{
			for (size_t i = 0; i < SIZE; ++i)
			{
				values[i] = array[i];
			}
		}

		TYPE & operator [] (size_t index)
		{
			return values[index];
		}

		const TYPE & operator [] (size_t index) const
		{
			return values[index];
		}

		Vector & operator += (const Vector & other)
		{
			for (size_t i = 0; i < SIZE; ++i)
			{
				this->values[i] += other.values[i];
			}

			return *this;
		}

		Vector operator + (const Vector & other) const
		{
			Vector result(this*);
			result += other;
			return result;
		}

		TYPE modulus() const
		{
			TYPE total = TYPE(0);

			for (size_t i = 0; i < SIZE; ++i)
			{
				total += values[i] * values[i];
			}

			return std::sqrt(total);
		}

		explicit operator TYPE () const
		{
			return modulus();
		}

	};

	template< typename TYPE >
	class Vector< TYPE, 3 >
	{

		//static_assert(SIZE > 0);

	public:

		TYPE values[3];

	public:

		Vector() = default;
		Vector(const Vector & other) = default;

		TYPE & x() { return values[0]; }
		TYPE & y() { return values[1]; }
		TYPE & z() { return values[2]; }

		const TYPE & x() const { return values[0]; }
		const TYPE & y() const { return values[1]; }
		const TYPE & z() const { return values[2]; }

	};

	typedef Vector< int,    2 > Vector2i;
	typedef Vector< float,  2 > Vector2f;
	typedef Vector< double, 2 > Vector2d;

	typedef Vector< int,    3 > Vector3i;
	typedef Vector< float,  3 > Vector3f;
	typedef Vector< double, 3 > Vector3d;

}