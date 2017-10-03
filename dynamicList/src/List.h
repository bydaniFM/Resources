/*
	Author: Daniel Fern�ndez
	Date: 03/10/2017

	DOXYGEN

	///< Comentario de lo que hay a la izquierda
	/// Comentario de lo que hay debajo
	/**
	* Otro comentario especial
*/

#pragma once

#include <cstddef>

namespace exercise {
	class List {
	private:	// Detalles de implementaci�n que no quiero dar a conocer

		struct Node {
			Node *prev;	///< Puntero al nodo previo (nullptr si es el primero de la lista)
			Node *next;	///< Puntero al siguiente nodo (nullptr si es el ultimo de la lista)
			int value;
		};

		Node *first;	///< Puntero al primer nodo de la lista
		Node *last;		///< Puntero al �ltimo nodo para optimizar el acceso por el final
		size_t count;

	public:

		class Iterator {

			friend class List;	//para poder usar las cosas en List

			Node *current;//nodo al que apunta el iterador en un momento dado
		private:
			Iterator(Node *node) :current(node) {}
		public:
			// Sobrecarga de operadores

			//Punteros
				  int & operator * ()		{ return current->value; }
			const int & operator * () const { return current->value; }

			//preincremento
			Iterator & operator ++ () {		//sobreescribimos el operador para poder recorrer iteradores
				if (current) current = current->next;
				return *this;
			}
			//postincremento
			Iterator & operator ++ (int) {
				Iterator copy = *this;
				if (current) current = current->next;
				return copy;
			}
			//predecremento
			Iterator & operator -- () {		//sobreescribimos el operador para poder recorrer iteradores
				if (current) current = current->prev;
				return *this;
			}
			//postdecremento
			Iterator & operator -- (int) {		//posincremento
				Iterator copy = *this;
				if (current) current = current->prev;
				return copy;
			}
			//igualdad
			bool operator == (const Iterator & other) const {
				return this->current == other.current;
			}
			//desigualdad
			bool operator != (const Iterator & other) const {
				return this->current != other.current;
			}
		};

	public:

		/// Crea una lista vac�a.
		List() {
			first = last = nullptr;
			count = 0;
		}

		/// Elimina todos los elementos que pueda haber en la lista cuando esta se destruye.
		~List() {
			if (!empty()) clear();
		}

		/// Retorna true si la lista est� vac�a.
		bool empty() const {
			return count == 0;
		}

		/// Retorna el n�mero de elementos que hay en la lista.
		size_t size() const {
			return count;
		}

		void clear();

		void pushFront(int value);
		void pushBack(int value);
		void popFront();
		void popBack();
		void insert(const Iterator & i, int value);	//inserta un elemento a continuaci�n
		void erase(const Iterator & i);				//borra el elemento en el iterador

		Iterator begin() { return Iterator(first); }	//devuelve iterador al primer elemento
		Iterator end() { return Iterator(nullptr); }		//devuelve iterador al pen�ltimo elemento

		/*int get(size_t index) {
			size_t count = 0;
			Node *current = first;
			while (count < index)			{
				current = current->next;
				count++;
			}
			return current->value;
		}*/
	};
}