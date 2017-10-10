/*
	Author: Daniel Fernández
	Date: 03/10/2017

	DOXYGEN

	///< Comentario de lo que hay a la izquierda
	/// Comentario de lo que hay debajo
	/**
	* Otro comentario especial
	...
*/

#pragma once

#include <cstddef>

namespace exercise {

	template<typename T>
	class List {
	public:
		typedef T Type;

	private:	// Detalles de implementación que no quiero dar a conocer

		struct Node {
			Node *prev;	///< Puntero al nodo previo (nullptr si es el primero de la lista)
			Node *next;	///< Puntero al siguiente nodo (nullptr si es el ultimo de la lista)
			T value;
		};

		Node *first;	///< Puntero al primer nodo de la lista
		Node *last;		///< Puntero al último nodo para optimizar el acceso por el final
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
				  T & operator * ()		{ return current->value; }
			const T & operator * () const { return current->value; }

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

		/// Crea una lista vacía.
		List() {
			first = last = nullptr;
			count = 0;
		}

		/// Elimina todos los elementos que pueda haber en la lista cuando esta se destruye.
		~List() {
			if (!empty()) clear();
		}

		/// Retorna true si la lista está vacía.
		bool empty() const {
			return count == 0;
		}

		/// Retorna el número de elementos que hay en la lista.
		size_t size() const {
			return count;
		}

		void clear();

		void pushFront(T value);
		void pushBack(T value);
		void popFront();
		void popBack();
		void insert(const Iterator & i, T value);	//inserta un elemento a continuación
		void erase(const Iterator & i);				//borra el elemento en el iterador

		Iterator begin() { return Iterator(first); }	//devuelve iterador al primer elemento
		Iterator end() { return Iterator(nullptr); }		//devuelve iterador al penúltimo elemento

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


	template<typename T>
	void List<T>::clear() {
		Node * current = first;

		while (current) {

			Node * next = current->next;

			delete current;

			current = next;
		}

		first = last = nullptr;
		count = 0;
	}

	template<typename T>
	void List<T>::pushFront(T value) {
		Node * new_node = new Node{ nullptr, first, value };

		if (first) {
			first->prev = new_node;
		}
		else {
			last = new_node;
		}
		first = new_node;
		count++;
	}

	template<typename T>
	void List<T>::pushBack(T value) {
		Node * new_node = new Node{ last, nullptr, value };

		if (last) {
			last->next = new_node;
		}
		else {
			first = new_node;
		}
		last = new_node;
		count++;
	}

	template<typename T>
	void List<T>::popFront() {
		if (first) {
			Node * next = first->next;

			delete first;
			first = next;

			if (first) {
				first->prev = nullptr;
			}
			else {
				last = nullptr;
			}
			--count;
		}
	}

	template<typename T>
	void List<T>::popBack() {
		if (last) {
			Node * prev = last->prev;

			delete last;
			last = prev;

			if (last) {
				last->next = nullptr;
			}
			else {
				first = nullptr;
			}
			count--;
		}
	}

	template<typename T>
	void List<T>::insert(const Iterator & i, T value) {

		Node * current = i.current;

		if (current == nullptr || current == last) {
			pushBack(value);
		}
		else {
			Node * new_node = new Node{ current, current->next, value };

			if (current->next) {
				current->next->prev = new_node;
			}
			current->next = new_node;
			count++;
		}
	}

	template<typename T>
	void List<T>::erase(const Iterator & i) {
		Node * current = i.current;

		if (current) {
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