/*
	Copyright...
	Licencia...
	Datos...
*/

#pragma once

#include <cstdint>

namespace lib
{

	class Memory_Pool
	{

		uint8_t * buffer;		///< Buffer donde se alojará memoria
		size_t    size;			///< Tamaño total del buffer
		size_t    allocated;	///< Cuánta memoria se ha alojado
		size_t    max_allocated;

	public:

		Memory_Pool(size_t buffer_size)
		{
			size      = buffer_size;
			buffer    = new uint8_t[size];
			allocated = max_allocated = 0;
		}

		~Memory_Pool()
		{
			delete [] buffer;
		}

		void * allocate(size_t number_of_bytes)
		{
			if (allocated + number_of_bytes < size)
			{
				void * address = buffer + allocated;

				allocated += number_of_bytes;

				if (allocated > max_allocated) max_allocated = allocated;

				return address;
			}
			else
				/// ALOJAR UN BUFFER ADICIONAL

			return nullptr;
		}
		
		template< typename TYPE >
		TYPE * allocate()
		{
			return reinterpret_cast< TYPE * >(allocate (sizeof(TYPE)));
		}

		void reset ()
		{
			allocated = 0;
		}

	};


}