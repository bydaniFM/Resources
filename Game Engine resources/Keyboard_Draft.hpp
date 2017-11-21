
#include <SDL.h>		// Crea dependencias

class Keyboard
{

	enum Key			// Crea dependencias
	{
		NUM_0 = SDLK_0,
		NUM_1 = SDLK_1,
		...
		A 	  = SDLK_a,
		...
		DOWN  = SDLK_DOWN,
		...
	};
	
	struct Key
	{
		static const int NUM_0;
	};
	
	enum Key
	{
		NUM_0,
		NUM_1,
		...
		A,
		...
		DOWN,
		...
	};

	
private:
	
	Key translate_key (int key_code);
	
};

// EN KEYBOARD.CPP --------------------------------

#include <SDL.h>		// No crea dependencias

Keyboard::Key Keyboard::translate_key (int key_code)
{
	switch (key_code)
	{
		case SDLK_0:    return NUM_0;
		case SDLK_DOWN: return DOWN;
	}
	
	return UNDEFINED;
}



