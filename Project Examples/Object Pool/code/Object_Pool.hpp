/*
	Copyright...
	Licencia...
	Datos...
*/

#pragma once

#include <cstdint>

namespace lib
{

	template< typename TYPE >
	class Object_Pool
	{
	public:

		typedef TYPE Object_Type;

	private:

		static const size_t object_size = sizeof(Object_Type);

		struct Node
		{
			TYPE   item;
			Node * prev;			// termina siendo innecesario
			Node * next;
		};


		uint8_t * buffer;
		Node    * free_nodes;
		Node    * used_nodes;

	public:

		Object_Pool(size_t object_count)
		{
			buffer = new uint8_t[object_count * sizeof(Node)];

			Node * current = reinterpret_cast< Node * >(buffer);

			free_nodes = current;
			used_nodes = nullptr;

			current->prev = nullptr;
			current->next = current + 1;

			for (size_t index = 1; index < object_count - 1; index++, current++)
			{
				current->prev = current - 1;
				current->next = current + 1;
			}

			current->prev = current - 1;
			current->next = nullptr;
		}

		~Object_Pool()
		{
			// Llamar a los destructores de la lista de nodos usados

			delete [] buffer;
		}

		Object_Type * allocate ()
		{
			if (free_nodes)
			{
				// Se toma el primer nodo de la lista libre:

				Node * node = free_nodes;

				// Se marca su siguiente como nuevo primer nodo libre:

				free_nodes = node->next;

				if (free_nodes) free_nodes->prev = nullptr;

				// Se añade el nodo al inicio de lista de nodos usados:

				if (used_nodes) used_nodes->prev = node;

				node->next = used_nodes;

				used_nodes = node;

				// Se reinterpreta la dirección del nodo como dirección de objeto:

				Object_Type * object = reinterpret_cast< Object_Type * >(node);

				// Se llama al constructor sin alojar memoria (PLACEMENT NEW):
				// new (object) TYPE (/*parámetros del constructor de Object_Type*/);

				new (object) Object_Type;

				return object;
			}
			else
				// ALOJAR E INICIALIZAR UN NUEVO BUFFER

			return nullptr;
		}

		void free (Object_Type * object)
		{
			if (object)
			{
				object->~Object_Type ();

				Node * node = reinterpret_cast< Node * >(object);

				// Se quita el nodo de la lista de nodos ocupados:

				if (node->prev) node->prev->next = node->next;
				if (node->next) node->next->prev = node->prev;

				// Se coloca al principio de la lista de nodos libres:

				node->prev = nullptr;
				node->next = free_nodes;
				free_nodes = node;
			}
		}
		

	};

}
