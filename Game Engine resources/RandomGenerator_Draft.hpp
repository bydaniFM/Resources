
class Random_Generator
{

	unsigned seed;

public:

	Random_Generator(unsigned seed) : seed(seed)
	{
	}
	
	unsigned next_random ()
	{
		seed *= 0xF0F0F0F0U;
	}
	
	unsigned operator () ()
	{
		return next_random ();
	}

};

---------------------------------------------------------------

Random_Generator x(0x12341234);

unsigned random_value = x();







