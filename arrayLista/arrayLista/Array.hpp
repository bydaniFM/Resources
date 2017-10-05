/*
	Author:	Daniel
	Date:	28-09-2017
*/

#pragma once

#include <cstddef>

namespace exercise {
	class Array {
	private:
		int *data;	//apunta al array
		size_t size;

	public:
		Array() : data(nullptr), size(0) {	//para inicializar data antes de entrar
		}
		Array(size_t initial_size);
		~Array() {
			if (size > 0) delete[]data;
		}

		size_t get_size() const { return size; }

		void clear();

		// Para poder acceder a un valor con los "[]"
		int & operator [] (size_t index) {
			return *(data + index);
		}

		// Sobrecarga para cuando se use const Array
		const int & operator [] (size_t index) const {
			return *(data + index);
		}

		// Para poder copiar arrays tenemos que sobreescibir el operador "="
		Array & operator = (const Array & other) {
			if (this != &other) {
				clear();

				if (other.size > 0) {
					this->data = new int[other.size];

					int *src = other.data;
					int *dst = this->data;

					for (int *end = src + other.size; src < end; ++src, ++dst) {
						*dst = *src;
					}
				} else {
					this->data = nullptr;
				}
				this->size = other.size;
			}
			return *this;
		}

		void push_back(int value);
		void pop_back();

		void insert(size_t index, int value);

		// Por si se quiere hacer la comprobación de que el index está dentro del array
		int & at(size_t index) {
			if (index >= size) {
				throw "error: index out of bounds";
				//throw out_of_bounds_exception();
			} else {
				return *(data + index);
			}
		}

		//Devuelve una referencia!
		int & get_item(size_t index) { return *(data + index); }

	};
}