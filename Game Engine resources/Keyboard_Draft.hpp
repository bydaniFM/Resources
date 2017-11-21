
#include <SDL.h>			// Crea dependencias por
// estar en una cabecera
class Keyboard
{

	enum Key
	{
		NUM_0 = SDLK_0,		// Crea dependencias
		NUM_1 = SDLK_1,
		...
		A = SDLK_a,
		...
		DOWN = SDLK_DOWN,
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

	/// Transforma un código de tecla de SDL en un
	/// código de tecla enumerado del engine.
	Key translate_key(int key_code);

};

// EN KEYBOARD.CPP --------------------------------

#include <SDL.h>		// No crea dependencias
// al estar en un CPP

Keyboard::Key Keyboard::translate_key(int key_code)
{
	switch (key_code)
	{
	case SDLK_0:    return NUM_0;
	case SDLK_DOWN: return DOWN;
	}

	return UNDEFINED;
}



