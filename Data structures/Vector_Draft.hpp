
template< typename TYPE, unsigned DIMENSION >
class Vector
{

	TYPE components[DIMENSION];

public:

	// -------------------------------------------
	// Constructores
	
	// No hacer nada en los constructores
	// por defecto
	Vector() = default;
	
	Vector(const TYPE (&values) [DIMENSION])
	{
		for (unsigned i = 0; i < DIMENSION; ++i)
		{
			components[i] = value[i];
		}
	}
	
	Vector(const std::initializer_list< TYPE > & )
	{
		// No se puede restringir el número de parámetros
	}
	
	Vector(const Vector & ) = default;

	template< typename OTHER_TYPE >
	explicit Vector(const Vector< OTHER_TYPE, DIMENSION > & other)
	{
		for (unsigned i = 0; i < DIMENSION; ++i)
		{
			components[i] = TYPE(other[i]);
		}
	}
	
	// -------------------------------------------
	// Métodos matemáticos
	
	TYPE squared_modulus () const
	{
		TYPE total = TYPE(0);
		
		for (unsigned i = 0; i < DIMENSION; ++i)
		{
			total += components[i] * components[i];
		}
		
		return total;
	}
	
	TYPE modulus () const
	{
		return TYPE(std::sqrt (squared_modulus ());
	}
	
	TYPE inverse_modulus () const
	{
		return TYPE(1) / modulus ();
	}
	
	Vector normalized () const
	{
		Vector normalized(*this);
		
		TYPE inv_mod = inverse_modulus ();
		
		for (unsigned i = 0; i < DIMENSION; ++i)
		{
			normalized[i] *= inv_mod;
		}
		
		return normalized;
	}
	
	// -------------------------------------------
	// Sobrecarga de operadores
	
	Vector & operator += (const Vector & other);
	Vector   operator +  (const Vector & other) const;
	Vector   operator +  () const;
	Vector & operator -= (const Vector & other);
	Vector   operator -  (const Vector & other) const;
	Vector   operator -  () const;
	Vector & operator *= (const Vector & other);
	Vector   operator *  (const Vector & other) const;
	Vector & operator /= (const Vector & other);
	Vector   operator /  (const Vector & other) const;

	bool	 operator == (const Vector & other) const;
	bool	 operator != (const Vector & other) const;
	
	TYPE & operator [] (unsigned index)
	{
		return components[index];
	}
	
	const TYPE & operator [] (unsigned index) const
	{
		return components[index];
	}
	

};

template< typename TYPE >
Vector< TYPE, 0 >;

typedef Vector< float, 2 > Vector2f;
typedef Vector< float, 3 > Vector3f;
typedef Vector< float, 4 > Vector4f;

typedef Vector< int , 2 > Vector2i;
typedef Vector< int , 3 > Vector3i;
typedef Vector< int , 4 > Vector4i;



template< typename TYPE, unsigned M, unsigned N >
class Matrix
{
	
	TYPE values[M * N];
	
};











