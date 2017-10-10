/*
	Author: Daniel Fernández
	Date: 10/10/2017
*/
class Vector3
{
public:

	static const Vector3 zero;
	static const Vector3 unit;
	
public:

	float x, y, z;

public:
	
	Vector3()
	{
	}
	
	Vector3(const Vector3 & other) :
		x(other.x),
		y(other.y),
		z(other.z)
	{
		
	}
	
	Vector3(float given_x, float given_y, float given_z)
	{
		x = given_x;
		y = given_y;
		z = given_z;
	}
	
	Vector3 & operator += (const Vector3 & other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}
	
	Vector3 operator + (const Vector3 & other) const
	{
		return Vector3(*this) += other;
	}
	
	const Vector3 & operator + () const
	{
		return *this;
	}
	
	float operator * (const Vector3 & other)
	{
		return this->x * other.x + this->y * other.y + this->z * other.z;
	}
	
	Vector3 & operator *= (float scalar)
	{
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
		return *this;
	}

	bool operator == (const Vector3 & other) const
	{
		return this->x == other.x && this->y == other.y && this->z == other.z;
	}
	
};

inline float operator * (float scalar, const Vector3 & other)
{
	return other * scalar;
}

//------------------------------------------------------------


const Vector3 Vector3::zero(0, 0, 0);
const Vector3 Vector3::unit(1, 1, 1);
