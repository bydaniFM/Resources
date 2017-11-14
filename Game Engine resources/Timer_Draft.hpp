
#include <chrono>

using std::chrono::high_resolution_clock;

class Timer
{

	high_resolution_clock::time_point start;

public:

	/// Inicia el cronometraje.
	void init ()
	{
		start = high_resolution_clock::now ();
	}
	
	/// Devuelve el número de segundos (con decimales) transcurridos
	/// desde que se llamó a init().
	double get_elapsed ()
	{
		high_resolution_clock::time_point now = high_resolution_clock::now ();
		
		return duration_cast< duration< double > >(now - start);
	}
	

};