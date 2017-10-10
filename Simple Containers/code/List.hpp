/*
	Autor: Ángel
	Fecha: 3.oct.2017
*/

#pragma once

#include <cstddef>

namespace example
{

	template< typename TYPE >
	class List
	{
	public:

		typedef TYPE Type;

	private:

		struct Node
		{
			Node * prev;			///< Puntero al nodo previo (nullptr si es el primero de la lista)
			Node * next;			///< Puntero al siguiente nodo (nullptr si es el último de la lista)
			TYPE   value;
		};

		Node * first;				///< Puntero al primer nodo de la lista
		Node * last;				///< Puntero al último nodo para optimizar el acceso por el final
		size_t count;				///< Guarda  el número de nodos de la lista

	public:

		class Iterator
		{
			friend class List;		///< Permite a List el acceso al constructor privado

			Node * current;			///< Nodo al que apunta el iterador en un momento dado

		private:

			Iterator(Node * node) : current(node)
			{
			}

		public:

			// Operadores de indirección:

			      TYPE & operator * ()       { return current->value; }
			const TYPE & operator * () const { return current->value; }

			// Operadores de avance:

			Iterator & operator ++ ()
			{
				if (current) current = current->next;
				return *this;
			}

			Iterator operator ++ (int)
			{
				Iterator copy = *this;
				if (current) current = current->next;
				return copy;
			}

			// Operadores de retroceso:

			Iterator & operator -- ()
			{
				if (current) current = current->prev;
				return *this;
			}

			Iterator operator -- (int)
			{
				Iterator copy = *this;
				if (current) current = current->prev;
				return copy;
			}

			// Operadores de comparación:

			bool operator == (const Iterator & other) const
			{
				return this->current == other.current;
			}

			bool operator != (const Iterator & other) const
			{
				return this->current != other.current;
			}

		};

	public:

        /// Crea una lista vacía.
		List()
		{
			first = last = nullptr;
			count = 0;
		}

        /// Elimina todos los elementos que pueda haber en la lista cuando esta se destruye.
	   ~List()
	    {
		   if (!empty ()) clear ();
	    }

        /// Retorna true si la lista está vacía.
        bool empty () const
        {
            return count == 0;
        }

        /// Retorna el número de elementos que hay en la lista.
        size_t size () const
		{
			return count;
		}

        /// Elimina todos los elementos que pueda haber en la lista.
		void clear ();

	    /// Añade un nuevo valor al final de la lista.
        void push_front (TYPE value);

        /// Añade un nuevo valor al principio de la lista.
	    void push_back (TYPE value);

        /// Elimina el último elemento de la lista.
	    void pop_front ();

        /// Elimina el primer elemento de la lista.
	    void pop_back ();

		/// Inserta un nuevo elemento en la lista a continuación del que se indica con el iterador.
        void insert (const Iterator & i, TYPE value);

        /// Elimina el elemento de la lista que se indica con el iterador.
		void erase (const Iterator & i);

        /// Retorna un iterador al primer elemento de la lista.
		Iterator begin ()
		{
			return Iterator(first);
		}

        /// Retorna un iterador a un elemento que marca el final de la lista. Dicho elemento no es válido (ni accesible).
		Iterator end ()
		{
			return Iterator(nullptr);
		}

	};

	template< typename TYPE >
	void List< TYPE >::clear()
	{
		Node * current = first;

		while (current)
		{
			Node * next = current->next;

			delete current;

			current = next;
		}

		first = last = nullptr;
		count = 0;
	}

	template< typename TYPE >
	void List< TYPE >::push_front(TYPE value)
	{
		Node * new_node = new Node{ nullptr, first, value };

		if (first)
		{
			first->prev = new_node;
		}
		else
		{
			last = new_node;
		}

		first = new_node;

		count++;
	}

	template< typename TYPE >
	void List< TYPE >::push_back(TYPE value)
	{
		Node * new_node = new Node{ last, nullptr, value };

		if (last)
		{
			last->next = new_node;
		}
		else
		{
			first = new_node;
		}

		last = new_node;

		count++;
	}

	template< typename TYPE >
	void List< TYPE >::pop_front()
	{
		if (first)
		{
			Node * next = first->next;

			delete first;

			first = next;

			if (first)
			{
				first->prev = nullptr;
			}
			else
			{
				last = nullptr;
			}

			--count;
		}
	}

	template< typename TYPE >
	void List< TYPE >::pop_back()
	{
		if (last)
		{
			Node * prev = last->prev;

			delete last;

			last = prev;

			if (last)
			{
				last->next = nullptr;
			}
			else
			{
				first = nullptr;
			}

			count--;
		}
	}

	template< typename TYPE >
	void List< TYPE >::insert(const Iterator & i, TYPE value)
	{
		Node * current = i.current;

		if (current == nullptr || current == last)
		{
			push_back(value);
		}
		else
		{
			Node * new_node = new Node{ current, current->next, value };

			if (current->next)
			{
				current->next->prev = new_node;
			}

			current->next = new_node;

			count++;
		}
	}

	template< typename TYPE >
	void List< TYPE >::erase(const Iterator & i)
	{
		Node * current = i.current;

		if (current)
		{
			Node * prev = current->prev;
			Node * next = current->next;

			if (current == first) first = next;
			if (current == last) last = prev;

			delete current;

			if (prev) prev->next = next;
			if (next) next->prev = prev;

			count--;
		}
	}

}
