/*
	Autor: �ngel
	Fecha: 3.oct.2017
*/

#pragma once

#include <cstddef>

namespace example
{

    // DOXYGEN

	class List
	{
	private:

		struct Node
		{
			Node * prev;			///< Puntero al nodo previo (nullptr si es el primero de la lista)
			Node * next;			///< Puntero al siguiente nodo (nullptr si es el �ltimo de la lista)
			int    value;
		};

		Node * first;				///< Puntero al primer nodo de la lista
		Node * last;				///< Puntero al �ltimo nodo para optimizar el acceso por el final
		size_t count;				///< Guarda  el n�mero de nodos de la lista

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

			// Operadores de indirecci�n:

			      int & operator * ()       { return current->value; }
			const int & operator * () const { return current->value; }

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

			// Operadores de comparaci�n:

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

        /// Crea una lista vac�a.
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

        /// Retorna true si la lista est� vac�a.
        bool empty () const
        {
            return count == 0;
        }

        /// Retorna el n�mero de elementos que hay en la lista.
        size_t size () const
		{
			return count;
		}

        /// Elimina todos los elementos que pueda haber en la lista.
		void clear ();

	    /// A�ade un nuevo valor al final de la lista.
        void push_front (int value);

        /// A�ade un nuevo valor al principio de la lista.
	    void push_back (int value);

        /// Elimina el �ltimo elemento de la lista.
	    void pop_front ();

        /// Elimina el primer elemento de la lista.
	    void pop_back ();

		/// Inserta un nuevo elemento en la lista a continuaci�n del que se indica con el iterador.
        void insert (const Iterator & i, int value);

        /// Elimina el elemento de la lista que se indica con el iterador.
		void erase (const Iterator & i);

        /// Retorna un iterador al primer elemento de la lista.
		Iterator begin ()
		{
			return Iterator(first);
		}

        /// Retorna un iterador a un elemento que marca el final de la lista. Dicho elemento no es v�lido (ni accesible).
		Iterator end ()
		{
			return Iterator(nullptr);
		}

	};

}
